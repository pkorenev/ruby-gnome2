
/*
 * Copyright (C) 2003 Laurent Sansonetti <laurent@datarescue.be>
 *
 * This file is part of Ruby/Libgda.
 *
 * Ruby/Libgda is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Ruby/Libgda is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Ruby/Libgda; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include "rbgda.h"

static VALUE rb_gda_error_new(self)
    VALUE self;
{
    GdaError *error = gda_error_new();
    if (error != NULL) {
        G_INITIALIZE(self, error);
    }
    return Qnil;
}

static VALUE rb_gda_error_get_description(self)
    VALUE self;
{
    return CSTR2RVAL(gda_error_get_description(RGDA_ERROR(self)));
}

static VALUE rb_gda_error_get_number(self)
    VALUE self;
{
    return INT2FIX(gda_error_get_number(RGDA_ERROR(self)));
}

static VALUE rb_gda_error_get_source(self)
    VALUE self;
{
    return CSTR2RVAL(gda_error_get_source(RGDA_ERROR(self)));
}

static VALUE rb_gda_error_get_sqlstate(self)
    VALUE self;
{
    return CSTR2RVAL(gda_error_get_sqlstate(RGDA_ERROR(self)));
}

static VALUE rb_gda_error_set_description(self, description)
    VALUE self, description;
{
    gda_error_set_description(RGDA_ERROR(self),
                              RVAL2CSTR(description));
    return self;
}

static VALUE rb_gda_error_set_number(self, number)
    VALUE self, number;
{
    gda_error_set_number(RGDA_ERROR(self),
                         FIX2INT(number));
    return self;
}

static VALUE rb_gda_error_set_source(self, source)
    VALUE self, source;
{
    gda_error_set_source(RGDA_ERROR(self),
                         RVAL2CSTR(source));
    return self;
}

static VALUE rb_gda_error_set_sqlstate(self, sqlstate)
    VALUE self, sqlstate;
{
    gda_error_set_sqlstate(RGDA_ERROR(self),
                           RVAL2CSTR(sqlstate));
    return self;
}

void Init_gda_error(void) {
    VALUE c = G_DEF_CLASS(GDA_TYPE_ERROR, "Error", mGda);

    rb_define_method(c, "initialize", rb_gda_error_new, 0);

    rb_define_method(c, "description", rb_gda_error_get_description, 0);
    rb_define_method(c, "number",      rb_gda_error_get_number,      0);
    rb_define_method(c, "source",      rb_gda_error_get_source,      0);
    rb_define_method(c, "sqlstate",    rb_gda_error_get_sqlstate,    0);

    rb_define_method(c, "set_description", rb_gda_error_set_description, 1);
    rb_define_method(c, "set_number",      rb_gda_error_set_number,      1);
    rb_define_method(c, "set_source",      rb_gda_error_set_source,      1);
    rb_define_method(c, "set_sqlstate",    rb_gda_error_set_sqlstate,    1);

    G_DEF_SETTERS(c);
}
