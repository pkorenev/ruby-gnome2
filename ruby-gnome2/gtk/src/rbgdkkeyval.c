/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgdkkeyval.c -

  $Author: mutoh $
  $Date: 2002/05/19 12:29:34 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

VALUE mGdkKeyval;

static VALUE
keyval_to_name(self, keyval)
    VALUE self, keyval;
{
    gchar* name = gdk_keyval_name(NUM2INT(keyval));
    return CSTR2OBJ(name);
}

static VALUE
keyval_from_name(self, keyval_name)
    VALUE self, keyval_name;
{
    return INT2NUM(gdk_keyval_from_name(STR2CSTR(keyval_name)));
}

static VALUE
keyval_is_upper(self, keyval)
    VALUE self, keyval;
{
    return (gdk_keyval_is_upper(NUM2INT(keyval))) ? Qtrue : Qfalse;
}

static VALUE
keyval_is_lower(self, keyval)
    VALUE self, keyval;
{
    return (gdk_keyval_is_lower(NUM2INT(keyval))) ? Qtrue : Qfalse;
}

static VALUE
keyval_to_upper(self, keyval)
    VALUE self, keyval;
{
    return INT2NUM(gdk_keyval_to_upper(NUM2INT(keyval)));
}

static VALUE
keyval_to_lower(self, keyval)
    VALUE self, keyval;
{
    return INT2NUM(gdk_keyval_to_lower(NUM2INT(keyval)));
}

void Init_gtk_gdk_keyval() {
    mGdkKeyval = rb_define_module_under(mGdk, "Keyval");
    rb_define_module_function(mGdkKeyval, "to_name", keyval_to_name, 1);
    rb_define_module_function(mGdkKeyval, "from_name", keyval_from_name, 1);
    rb_define_module_function(mGdkKeyval, "upper?", keyval_is_upper, 1);
    rb_define_module_function(mGdkKeyval, "lower?", keyval_is_lower, 1);
    rb_define_module_function(mGdkKeyval, "to_upper", keyval_to_upper, 1);
    rb_define_module_function(mGdkKeyval, "to_lower", keyval_to_lower, 1);
}
