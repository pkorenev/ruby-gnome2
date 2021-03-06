
/*
 * Copyright (C) 2003, 2004 Laurent Sansonetti <lrz@gnome.org>
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

/*
 * Class: Gda::Provider
 * Information about providers which are installed in the system.
 */
VALUE cGdaProvider;

/*
 * Class method: providers
 *
 * Returns: a list of all providers currently installed in the system, as an
 * Array of Gda::Provider objects.
 */
static VALUE rb_gda_get_providers(self)
    VALUE self;
{
    GList *list, *node;
    VALUE arr;

    list = gda_config_get_provider_list();
    arr = rb_ary_new();

    for (node = g_list_first(list); 
         node != NULL;
         node = g_list_next(node))
    {
        rb_ary_push(arr, RGDA_PROVIDER_NEW(node->data));
    }
    gda_config_free_provider_list(list);

    return arr;
}

/*
 * Class method: each_provider { |provider| ... }
 *
 * Calls the block for each provider which is currently installed in the
 * system, passing a reference to a Gda::Provider object as parameter.
 *
 * Returns: always nil.
 */
static VALUE rb_gda_provider_each(self)
    VALUE self;
{
    rb_ary_each(rb_gda_get_providers(self));
    return Qnil;
}

#if defined(GDA_AT_LEAST_1_1)
/*
 * Class method: model
 *
 * Fills and returns a new Gda::DataModel object using information from all
 * providers which are currently installed in the system.
 *
 * Rows are separated in 3 columns:
 * 'Id', 'Location' and 'Description'.
 *
 * Returns: a new Gda::DataModel object.
 */
static VALUE rb_gda_provider_model(self)
    VALUE self;
{
    GdaDataModel *model = gda_config_get_provider_model();
    return model != NULL
        ? RGDA_DATAMODEL_NEW(model)
        : Qnil;
}
#endif /* GDA_AT_LEAST_1_1 */

/*
 * Class method: get_by_name(name)
 * name: name of the provider to search for.
 *
 * Gets a Gda::Provider object from the provider list givin its name.
 *
 * Returns: a Gda::Provider object if found, nil if not found.
 */
static VALUE rb_gda_provider_get_by_name(self, name)
    VALUE self, name;
{
    GdaProviderInfo *info = gda_config_get_provider_by_name(RVAL2CSTR(name));
    return info != NULL
        ? RGDA_PROVIDER_NEW(info)
        : Qnil;
}

/*
 * Method: prov_id
 *
 * Returns: the provider's ID (usually its name).
 */
static VALUE rb_gda_provider_get_id(self)
    VALUE self;
{
    GdaProviderInfo *info = RGDA_PROVIDER(self);
    return CSTR2RVAL(info->id);
}

/*
 * Method: location
 *
 * Returns: the provider's location (usually, the file name where it came
 * from).
 */
static VALUE rb_gda_provider_get_location(self)
    VALUE self;
{
    GdaProviderInfo *info = RGDA_PROVIDER(self);
    return CSTR2RVAL(info->location);
}

/*
 * Method: description
 *
 * Returns: the provider's description.
 */
static VALUE rb_gda_provider_get_description(self)
    VALUE self;
{
    GdaProviderInfo *info = RGDA_PROVIDER(self);
    return CSTR2RVAL(info->description);
}

/*
 * Method: ==(an_other_provider)
 * an_other_provider: a Gda::Provider object.
 *
 * Returns: true if the two Gda::Provider are referring the same provider,
 * false otherwise.
 */
static VALUE rb_gda_provider_is_equal(self, other_prov)
    VALUE self, other_prov;
{
    return NIL_P(other_prov)
        ? Qfalse
        : rb_equal(rb_gda_provider_get_id(self),
                   rb_gda_provider_get_id(other_prov));
}

void Init_gda_provider(void) {
    VALUE c = G_DEF_CLASS(GDA_TYPE_PROVIDER_INFO, "Provider", mGda);

    rb_define_singleton_method(c, "providers", rb_gda_get_providers,  0);
    rb_define_singleton_method(c, "each",      rb_gda_provider_each,  0);
#if defined(GDA_AT_LEAST_1_1)
    rb_define_singleton_method(c, "model",     rb_gda_provider_model, 0);
#endif
    rb_define_singleton_method(c, "get_by_name", 
                               rb_gda_provider_get_by_name, 1);

    rb_define_method(c, "prov_id",     rb_gda_provider_get_id,          0);
    rb_define_alias(c, "name", "prov_id");
    rb_define_method(c, "location",    rb_gda_provider_get_location,    0);
    rb_define_method(c, "description", rb_gda_provider_get_description, 0);

    rb_define_method(c, "==", rb_gda_provider_is_equal, 1);

    cGdaProvider = c;
}

