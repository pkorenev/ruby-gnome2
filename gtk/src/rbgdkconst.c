/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgdkconst.c -

  $Author: sakai $
  $Date: 2003/08/20 17:07:02 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

/*
 * Gdk module constants
 */
void
Init_gtk_gdk_const()
{
    /* GdkStatus */
    G_DEF_CLASS(GDK_TYPE_STATUS, "Status", mGdk);
    G_DEF_CONSTANTS(mGdk, GDK_TYPE_STATUS, "GDK_");

    /* GdkInputSource */
    /* This will move to Gdk::Device.
    rb_define_const(mGdk, "SOURCE_MOUSE", INT2FIX(GDK_SOURCE_MOUSE));
    rb_define_const(mGdk, "SOURCE_PEN", INT2FIX(GDK_SOURCE_PEN));
    rb_define_const(mGdk, "SOURCE_ERASER", INT2FIX(GDK_SOURCE_ERASER));
    rb_define_const(mGdk, "SOURCE_CURSOR", INT2FIX(GDK_SOURCE_CURSOR));
    */

    /* GdkInputMode */
    /* This will move to Gdk::Device.
    rb_define_const(mGdk, "MODE_DISABLED", INT2FIX(GDK_MODE_DISABLED));
    rb_define_const(mGdk, "MODE_SCREEN", INT2FIX(GDK_MODE_SCREEN));
    rb_define_const(mGdk, "MODE_WINDOW", INT2FIX(GDK_MODE_WINDOW));
    */

    /* GdkAxisUse */
    /* This will move to Gdk::Device.
    rb_define_const(mGdk, "AXIS_IGNORE", INT2FIX(GDK_AXIS_IGNORE));
    rb_define_const(mGdk, "AXIS_X", INT2FIX(GDK_AXIS_X));
    rb_define_const(mGdk, "AXIS_Y", INT2FIX(GDK_AXIS_Y));
    rb_define_const(mGdk, "AXIS_PRESSURE", INT2FIX(GDK_AXIS_PRESSURE));
    rb_define_const(mGdk, "AXIS_XTILT", INT2FIX(GDK_AXIS_XTILT));
    rb_define_const(mGdk, "AXIS_YTILT", INT2FIX(GDK_AXIS_YTILT));
    rb_define_const(mGdk, "AXIS_LAST", INT2FIX(GDK_AXIS_LAST));
    */

    /* GdkExtensionMode */
    /* This will move to Gdk::Device.
    rb_define_const(mGdk, "EXTENSION_EVENTS_NONE", INT2FIX(GDK_EXTENSION_EVENTS_NONE));
    rb_define_const(mGdk, "EXTENSION_EVENTS_ALL", INT2FIX(GDK_EXTENSION_EVENTS_ALL));
    rb_define_const(mGdk, "EXTENSION_EVENTS_CURSOR", INT2FIX(GDK_EXTENSION_EVENTS_CURSOR));
    */
}


