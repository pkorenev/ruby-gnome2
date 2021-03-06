/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/**********************************************************************

  rbart_affine.c - Art::Affine class of ruby

  $Author: ggc $
  $Date: 2007/07/13 16:07:33 $

  Copyright (C) 2004  Ruby-GNOME2 Project Team
  Copyright (C) 2002,2003  KUBO Takehiro <kubo@jiubao.org>

**********************************************************************/

#include "rbart.h"

VALUE artAffine;

/* Below 2 macros are available only when obj is self or after
 * checking that obj is certainly a instance of Art::Affine. */
#define Affine_Ptr(obj) ((double *)(RDATA(obj)->data))
#define Affine_Set(obj, val) memcpy(Affine_Ptr(obj), val, sizeof(double[6]))

/**********************************************************/
double *
get_art_affine(obj)
    VALUE obj;
{
    if (!rb_obj_is_instance_of(obj, artAffine))
        rb_raise(rb_eTypeError, "not an ArtAffine");
    return Affine_Ptr(obj);
}

VALUE
make_art_affine(affine)
    double affine[6];
{
    double *ptr = xmalloc(sizeof(double[6]));
    memcpy(ptr, affine, sizeof(double[6]));
    return Data_Wrap_Struct(artAffine, 0, xfree, ptr);
}
/**********************************************************/

static VALUE
affine_initialize(argc, argv, klass)
    int argc;
    VALUE *argv;
    VALUE klass;
{
    int i;
    double* affine = xmalloc(sizeof(double[6]));

    if (argc == 1) {
        Check_Type(argv[0], T_ARRAY);
        if (RARRAY_LEN(argv[0]) != 6)
            rb_raise(rb_eArgError, "wrong size of Array (expect 6)");
        argv = RARRAY_PTR(argv[0]);
    } else if (argc != 6) {
        rb_raise(rb_eArgError, "wrong # of argument (expect an array(5 members) or 6 parameters)");
    }
    for (i = 0;i < 6;i++)
        affine[i] = NUM2DBL(argv[i]);

    RDATA(klass)->data = affine;

    return Qnil;
}

static VALUE
affine_s_identity(klass)
    VALUE klass;
{
    double affine[6];
    art_affine_identity(affine);
    return make_art_affine(affine);
}

static VALUE
affine_s_scale(klass, sx, sy)
    VALUE klass, sx, sy;
{
    double affine[6];
    art_affine_scale(affine, NUM2DBL(sx), NUM2DBL(sy));
    return make_art_affine(affine);
}

static VALUE
affine_s_rotate(klass, theta)
    VALUE klass, theta;
{
    double affine[6];
    art_affine_rotate(affine, NUM2DBL(theta));
    return make_art_affine(affine);
}

static VALUE
affine_s_shear(klass, theta)
    VALUE klass, theta;
{
    double affine[6];
    art_affine_shear(affine, NUM2DBL(theta));
    return make_art_affine(affine);
}

static VALUE
affine_s_translate(klass, tx, ty)
    VALUE klass, tx, ty;
{
    double affine[6];
    art_affine_translate(affine, NUM2DBL(tx), NUM2DBL(ty));
    return make_art_affine(affine);
}

static VALUE
affine_point(argc, argv, self)
    int argc;
    VALUE *argv, self;
{
    ArtPoint src;
    ArtPoint dst;

    if (argc == 1) {
        if (TYPE(argv[0]) != T_ARRAY)
            goto arg_error;
        if (RARRAY_LEN(argv[0]) != 2)
            goto arg_error;
        src.x = NUM2DBL(RARRAY_PTR(argv[0])[0]);
        src.y = NUM2DBL(RARRAY_PTR(argv[0])[1]);
    } else if (argc == 2) {
        src.x = NUM2DBL(argv[0]);
        src.y = NUM2DBL(argv[1]);
    } else {
        goto arg_error;
    }
    art_affine_point(&dst, &src, Affine_Ptr(self));
    return rb_ary_new3(2, rb_float_new(dst.x), rb_float_new(dst.y));
  arg_error:
    rb_raise(rb_eArgError, "wrong argument format (expect (x, y) or ([x, y]).)");
}

static VALUE
affine_invert(self)
    VALUE self;
{
    double affine[6];
    art_affine_invert(affine, Affine_Ptr(self));
    return make_art_affine(affine);
}

static VALUE
affine_invert_bang(self)
    VALUE self;
{
    double affine[6];
    art_affine_invert(affine, Affine_Ptr(self));
    Affine_Set(self, affine);
    return self;
}

static VALUE
affine_flip(self, horz, vert)
    VALUE self, horz, vert;
{
    double affine[6];
    art_affine_flip(affine, Affine_Ptr(self), RVAL2CBOOL(horz), RVAL2CBOOL(vert));
    return make_art_affine(affine);
}

static VALUE
affine_flip_bang(self, horz, vert)
    VALUE self, horz, vert;
{
    double affine[6];
    art_affine_flip(affine, Affine_Ptr(self), RVAL2CBOOL(horz), RVAL2CBOOL(vert));
    Affine_Set(self, affine);
    return self;
}

static VALUE
affine_to_s(self)
    VALUE self;
{
    char str[255];
    VALUE ret;
    double* affine = Affine_Ptr(self);
    if (affine)
        art_affine_to_string(str, affine);
    else
        str[0] = '\0';
    
    ret = rb_str_new2("<");
    rb_str_cat2(ret, rb_class2name(CLASS_OF(self)));
    if (str[0] != '\0') {
        rb_str_cat2(ret, ":");
        rb_str_cat2(ret, str);
    }
    rb_str_cat2(ret, ">");
    return ret;
}

static VALUE
affine_to_a(self)
    VALUE self;
{
    double *affine = Affine_Ptr(self);
    return rb_ary_new3(6, rb_float_new(affine[0]), rb_float_new(affine[1]), 
                       rb_float_new(affine[2]), rb_float_new(affine[3]), 
                       rb_float_new(affine[4]), rb_float_new(affine[5]));
}

static VALUE
affine_expansion(self)
    VALUE self;
{
    return rb_float_new(art_affine_expansion(Affine_Ptr(self)));
}

static VALUE
affine_rectiliner(self)
    VALUE self;
{
    return CBOOL2RVAL(art_affine_rectilinear(Affine_Ptr(self)));
}

static VALUE
affine_multiply(self, right)
    VALUE self, right;
{
    double affine[6];
    art_affine_multiply(affine, get_art_affine(right), Affine_Ptr(self));
    return make_art_affine(affine);
}

static VALUE
affine_equal(self, right)
    VALUE self, right;
{
    if (!rb_obj_is_instance_of(right, artAffine)) {
        return Qfalse;
    }
    return CBOOL2RVAL(art_affine_equal(Affine_Ptr(self), Affine_Ptr(right)));
}

void
Init_art_affine(mArt)
    VALUE mArt;
{
    artAffine = rb_define_class_under(mArt, "Affine", rb_cData);

    RBART_INIT_FUNC(artAffine);

    rb_define_singleton_method(artAffine, "identity", affine_s_identity, 0);
    rb_define_singleton_method(artAffine, "scale", affine_s_scale, 2);
    rb_define_singleton_method(artAffine, "rotate", affine_s_rotate, 1);
    rb_define_singleton_method(artAffine, "shear", affine_s_shear, 1);
    rb_define_singleton_method(artAffine, "translate", affine_s_translate, 2);

    rb_define_method(artAffine, "initialize", affine_initialize, -1);

    rb_define_method(artAffine, "point", affine_point, -1);
    rb_define_method(artAffine, "invert", affine_invert, 0);
    rb_define_method(artAffine, "invert!", affine_invert_bang, 0);
    rb_define_method(artAffine, "flip", affine_flip, 2);
    rb_define_method(artAffine, "flip!", affine_flip_bang, 2);
    rb_define_method(artAffine, "to_s", affine_to_s, 0);
    rb_define_method(artAffine, "to_a", affine_to_a, 0);
    rb_define_method(artAffine, "expansion", affine_expansion, 0);
    rb_define_method(artAffine, "rectiliner", affine_rectiliner, 0);

    rb_define_method(artAffine, "*", affine_multiply, 1);
    rb_define_method(artAffine, "==", affine_equal, 1);

    rb_define_alias(artAffine, "inverse", "invert");
    rb_define_alias(artAffine, "inverse!", "invert!");
    rb_define_alias(artAffine, "call", "point");
    rb_define_alias(artAffine, "[]", "point");
    rb_define_alias(artAffine, "act", "point");
}
