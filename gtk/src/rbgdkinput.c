/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgdkinput.c -

  $Author: mutoh $
  $Date: 2003/05/08 16:45:59 $

  Copyright (C) 2002,2003 Masao Mutoh

  This file is devided from rbgtkmain.c.
  rbgtkmain.c -
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static void
exec_input(data, source, condition)
    gpointer data;
    gint source;
    GdkInputCondition condition;
{
    rb_funcall((VALUE)data, id_call, 0);
}

static VALUE
input_add(self, filedescriptor, gdk_input_condition)
    VALUE self, filedescriptor, gdk_input_condition;
{
    VALUE id;
    VALUE func;

    func = rb_f_lambda();
    id = INT2FIX(gdk_input_add(NUM2INT(rb_funcall(filedescriptor,
                                                  rb_intern("to_i"), 0)),
                               (GdkInputCondition)NUM2INT(gdk_input_condition),
                               (GdkInputFunction)exec_input,
                               (gpointer)func));
    G_RELATIVE2(self, func, id_relative_callbacks, id);
    return id;
}

static VALUE
input_remove(self, id)
    VALUE self, id;
{
    gdk_input_remove(NUM2INT(id));
    G_REMOVE_RELATIVE(self, id_relative_callbacks, id);
    return id;
}

/* This method from 'Input Devices' */
static VALUE
input_set_extension_events(self, window, mask, mode)
    VALUE self, window, mask, mode;
{
    gdk_input_set_extension_events(GDK_WINDOW(RVAL2GOBJ(window)),
                                   NUM2INT(mask), FIX2INT(mode));
    return Qnil;
}

void
Init_gtk_gdk_input()
{
    VALUE mGdkInput = rb_define_module_under(mGdk, "Input");

    rb_define_module_function(mGdkInput, "add", input_add, 2);
    rb_define_module_function(mGdkInput, "remove", input_remove, 1);
    rb_define_module_function(mGdkInput, "set_extension_events", input_set_extension_events, 3);

    /* GdkInputCondition */
    rb_define_const(mGdkInput, "READ", INT2FIX(GDK_INPUT_READ));
    rb_define_const(mGdkInput, "WRITE", INT2FIX(GDK_INPUT_WRITE));
    rb_define_const(mGdkInput, "EXCEPTION", INT2FIX(GDK_INPUT_EXCEPTION));

    /* GdkExtensionMode */
    rb_define_const(mGdkInput, "EXTENSION_EVENTS_NONE", INT2FIX(GDK_EXTENSION_EVENTS_NONE));
    rb_define_const(mGdkInput, "EXTENSION_EVENTS_ALL", INT2FIX(GDK_EXTENSION_EVENTS_ALL));
    rb_define_const(mGdkInput, "EXTENSION_EVENTS_CURSOR", INT2FIX(GDK_EXTENSION_EVENTS_CURSOR));

}
