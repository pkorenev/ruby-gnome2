/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/* $Id: rbgnome-messagebox.c,v 1.3 2002/09/25 17:17:24 tkubo Exp $ */

/* Gnome::MessageBox widget for Ruby/Gnome
 * Copyright (C) 1999 Minoru Inachi <inachi@earth.interq.or.jp>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "rbgnome.h"

static VALUE
mesbox_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE message, messagebox_type, buttons;
    const gchar **c_buttons;
    int i;
    GtkWidget* message_box;

    rb_scan_args(argc, argv, "2*", &message, &messagebox_type, &buttons);

    c_buttons = ALLOCA_N(const gchar*, RARRAY(buttons)->len+1);
    for (i = 0; i < RARRAY(buttons)->len; i++) {
        c_buttons[i] = RVAL2CSTR(RARRAY(buttons)->ptr[i]);
    }
    c_buttons[i] = 0;

    message_box = gnome_message_box_newv(RVAL2CSTR(message),
                                         RVAL2CSTR(messagebox_type),
                                         c_buttons);
    RBGTK_INITIALIZE(self, message_box);
    return Qnil;
}

void
Init_gnome_messagebox(mGnome)
    VALUE mGnome;
{
    VALUE gnoMessageBox = G_DEF_CLASS(GNOME_TYPE_MESSAGE_BOX, "MessageBox", mGnome);

    /* Constants */
    rb_define_const(gnoMessageBox, "INFO", rb_str_new2(GNOME_MESSAGE_BOX_INFO));
    rb_define_const(gnoMessageBox, "WARNING", rb_str_new2(GNOME_MESSAGE_BOX_WARNING));
    rb_define_const(gnoMessageBox, "ERROR", rb_str_new2(GNOME_MESSAGE_BOX_ERROR));
    rb_define_const(gnoMessageBox, "QUESTION", rb_str_new2(GNOME_MESSAGE_BOX_QUESTION));
    rb_define_const(gnoMessageBox, "GENERIC", rb_str_new2(GNOME_MESSAGE_BOX_GENERIC));

    /* Instance methods */
    rb_define_method(gnoMessageBox, "initialize", mesbox_initialize, -1);
}
