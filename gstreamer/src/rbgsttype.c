
/*
 * Copyright (C) 2003 Laurent Sansonetti <laurent@datarescue.be>
 *
 * This file is part of Ruby/GStreamer.
 *
 * Ruby/GStreamer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Ruby/GStreamer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Ruby/GStreamer; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include "rbgst.h"

/*
 *  Class: Gst::Type
 *
 *  Identifies the data. 
 */

static GstType* type_copy(const GstType* type) {
    GstType* new_type;
    g_return_val_if_fail (type != NULL, NULL);
    new_type = g_new(GstType, 1);
    *new_type = *type;
    return new_type;
}

GType gst_type_get_type(void) {
    static GType our_type = 0;
    if (our_type == 0) {
        our_type = g_boxed_type_register_static ("GstType",
            (GBoxedCopyFunc)type_copy,
            (GBoxedFreeFunc)g_free);
    }
    return our_type;
}

/*
 *  Class method: types -> anArray
 *
 *  Returns a list of all registered types, in an array 
 *  of Gst::Type objects.
 */
static VALUE rb_gst_type_get_types(self)
    VALUE self;
{
    VALUE arr;
    GList *list;

    arr = rb_ary_new();
    for (list = (GList *) gst_type_get_list(); list != NULL; list = g_list_next(list)) {
        rb_ary_push(arr, RGST_TYPE_NEW((GstType *)list->data));
    }

    return arr;
}

/*
 *  Class method: each { |aTypeObject| block } -> nil
 *
 *  Calls the block for each registred types, passing a reference to
 *  the Gst::Type as parameter. 
 */
static VALUE rb_gst_type_each(self)
    VALUE self;
{
    return rb_ary_yield(rb_gst_type_get_types(self));
}

/*
 *  Class method: find_by_id(aFixnum) -> aTypeObject
 *
 *  Searches for a registered type of the given ID.  
 *  If found, returns a Gst::Type object. Otherwise, returns nil. 
 */
static VALUE rb_gst_type_find_by_id(self, id)
    VALUE self, id;
{
    GstType *type = gst_type_find_by_id(FIX2INT(id));
    return type != NULL 
        ? RGST_TYPE_NEW(type)
        : Qnil;
}

/*
 *  Class method: find_by_mime(aString) -> aTypeObject
 *
 *  Searches for a registered type of the given MIME type.  
 *  If found, returns a Gst::Type object.  Otherwise, returns nil. 
 */
static VALUE rb_gst_type_find_by_mime(self, mime)
    VALUE self, mime;
{
    guint16 id    = gst_type_find_by_mime(RVAL2CSTR(mime));
    GstType *type = gst_type_find_by_id(id);
    return type != NULL 
        ? RGST_TYPE_NEW(type)
        : Qnil;
}

/*
 *  Method: id -> aFixnum
 *
 *  Gets the ID number of the type.
 */
static VALUE rb_gst_type_get_id(self)
    VALUE self;
{
    GstType *type = RGST_TYPE(self);
    return INT2FIX(type->id);
}

/*
 *  Method: mime -> aString
 *
 *  Gets the MIME type of the type. 
 */
static VALUE rb_gst_type_get_mime(self)
    VALUE self;
{
    GstType *type = RGST_TYPE(self);
    return CSTR2RVAL(type->mime);
}

/*
 *  Method: exts -> aString
 *
 *  Gets files extentions handled by the type, if there
 *  are any.  This method may otherwise return nil. 
 */
static VALUE rb_gst_type_get_exts(self)
    VALUE self;
{
    GstType *type = RGST_TYPE(self);
    return CSTR2RVAL(type->exts);
}

/*
 *  Method: == aTypeObject -> aBoolean
 *
 *  Checks if two Gst::Type objects are refered under the same ID number.
 */
static VALUE rb_gst_type_is_equal(self, other_type)
    VALUE self, other_type;
{
    return rb_equal(rb_gst_type_get_id(self), 
                    rb_gst_type_get_id(other_type));
}

void Init_gst_type(void) {
    VALUE c = G_DEF_CLASS(GST_TYPE_TYPE, "Type", mGst); 
    
    rb_define_singleton_method(c, "types", rb_gst_type_get_types, 0);
    rb_define_singleton_method(c, "each", rb_gst_type_each, 0);

    rb_define_singleton_method(c, "find_by_id",   rb_gst_type_find_by_id,   1);
    rb_define_singleton_method(c, "find_by_mime", rb_gst_type_find_by_mime, 1);
    
    rb_define_method(c, "id",   rb_gst_type_get_id,   0);
    rb_define_method(c, "mime", rb_gst_type_get_mime, 0);
    rb_define_method(c, "exts", rb_gst_type_get_exts, 0);

    rb_define_method(c, "==", rb_gst_type_is_equal, 1);
}
