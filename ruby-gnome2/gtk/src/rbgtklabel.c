/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtklabel.c -

  $Author: mutoh $
  $Date: 2002/05/19 12:29:39 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
label_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE label;
    rb_scan_args(argc, argv, "01", &label);
    set_widget(self, gtk_label_new(NIL_P(label)?NULL:STR2CSTR(label)));
    return Qnil;
}

static VALUE
label_get(self)
    VALUE self;
{
    gchar* str;
    gtk_label_get(GTK_LABEL(get_widget(self)), &str);
    return rb_str_new2(str);
}

static VALUE
label_set_text(self, str)
    VALUE self, str;
{
    gtk_label_set_text(GTK_LABEL(get_widget(self)), STR2CSTR(str));
    return Qnil;
}

static VALUE
label_get_jtype(self)
    VALUE self;
{
    return INT2FIX(GTK_LABEL(get_widget(self))->jtype);
}

static VALUE
label_set_jtype(self, jtype)
    VALUE self, jtype;
{
    GtkJustification j;
    j = (GtkJustification) NUM2INT(jtype);
    gtk_label_set_justify(GTK_LABEL(get_widget(self)), j);
    return self;
}

static VALUE
label_set_line_wrap(self, wrap)
    VALUE self, wrap;
{
    gtk_label_set_line_wrap(GTK_LABEL(get_widget(self)), (gboolean)RTEST(wrap));
    return self;
}

static VALUE
label_set_pattern(self, pattern)
    VALUE self, pattern;
{
    gtk_label_set_pattern(GTK_LABEL(get_widget(self)), STR2CSTR(pattern));
    return self;
}

static VALUE
label_parse_uline(self, string)
    VALUE self, string;
{
    guint i = gtk_label_parse_uline(GTK_LABEL(get_widget(self)),
				    STR2CSTR(string));
    return INT2FIX(i);
}

void Init_gtk_label()
{
    gLabel = rb_define_class_under(mGtk, "Label", gMisc);

    rb_define_method(gLabel, "initialize", label_initialize, -1);
    rb_define_method(gLabel, "get", label_get, 0);
    rb_define_alias(gLabel, "get_text", "get");
    rb_define_alias(gLabel, "text", "get");
    rb_define_method(gLabel, "set", label_set_text, 1);
    rb_define_alias(gLabel, "set_text", "set");
    rb_define_alias(gLabel, "text=", "set");
    rb_define_method(gLabel, "jtype", label_get_jtype, 0);
    rb_define_method(gLabel, "jtype=", label_set_jtype, 1);
    rb_define_method(gLabel, "set_line_wrap", label_set_line_wrap, 1);
    rb_define_method(gLabel, "set_pattern", label_set_pattern, 1);
    rb_define_method(gLabel, "parse_uline", label_parse_uline, 1);

    rb_define_alias(gLabel, "get_justify", "jtype");
    rb_define_alias(gLabel, "set_justify", "jtype=");

    /* child initialize */
    Init_gtk_tips_query();
    Init_gtk_accel_label();
}
