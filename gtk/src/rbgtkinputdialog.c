/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtkinputdialog.c -

  $Author: mutoh $
  $Date: 2002/07/31 17:23:54 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
idiag_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_input_dialog_new());
    return Qnil;
}

void Init_gtk_input_dialog()
{
    VALUE gInputDialog = G_DEF_CLASS(GTK_TYPE_INPUT_DIALOG, "InputDialog", mGtk);
    rb_define_const(gInputDialog, "SIGNAL_ENABLE_DEVICE", rb_str_new2("enable_device"));
    rb_define_const(gInputDialog, "SIGNAL_DISABLE_DEVICE", rb_str_new2("disable_device"));

    rb_define_method(gInputDialog, "initialize", idiag_initialize, 0);
}
