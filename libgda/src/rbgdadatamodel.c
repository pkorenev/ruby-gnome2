
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
 * Class: Gda::DataModel
 * Basic data model class.
 */
VALUE cGdaDataModel;

/*
 * Method: emit_changed
 *
 * Notifies listeners of the given data model object of changes in the
 * underlying data. Listeners usually will connect themselves to the "changed"
 * signal in the Gda::DataModel class, thus being notified of any new data
 * being appended or removed from the data model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_changed(self)
    VALUE self;
{
    gda_data_model_changed(RGDA_DATAMODEL(self));
    return self;
}

/*
 * Method: emit_row_inserted(rownum)
 * rownum: a row number.
 *
 * Emits the 'row_inserted' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_row_inserted(self, rownum)
    VALUE self, rownum;
{
    gda_data_model_row_inserted(RGDA_DATAMODEL(self), 
                                FIX2INT(rownum));
    return self;
}

/*
 * Method: emit_row_updated(rownum)
 * rownum: a row number.
 *
 * Emits the 'row_updated' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_row_updated(self, rownum)
    VALUE self, rownum;
{
    gda_data_model_row_updated(RGDA_DATAMODEL(self),
                               FIX2INT(rownum));
    return self;
}

/*
 * Method: emit_row_removed(rownum)
 * rownum: a row number.
 *
 * Emits the 'row_removed' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_row_removed(self, rownum)
    VALUE self, rownum;
{
    gda_data_model_row_removed(RGDA_DATAMODEL(self),
                               FIX2INT(rownum));
    return self;
}

/*
 * Method: freeze!
 *
 * Disables notifications of changes on the data model. To re-enable
 * notifications again, you should call the Gda::DataModel#thaw method. 
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_freeze(self)
    VALUE self;
{
    gda_data_model_freeze(RGDA_DATAMODEL(self));
    return self;
}

/*
 * Method: thaw!
 *
 * Re-enables notifications of changes on the given data model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_thaw(self)
    VALUE self;
{
    gda_data_model_thaw(RGDA_DATAMODEL(self));
    return self;
}

/*
 * Method: columns
 *
 * Returns: a list of all column titles in the model, as an Array of strings.
 */
static VALUE rb_gda_datamodel_get_columns(self)
    VALUE self;
{
    GdaDataModel *datamod;
    VALUE arr;
    int i;

    arr = rb_ary_new();
    datamod = RGDA_DATAMODEL(self);
    for (i = 0; i < gda_data_model_get_n_columns(datamod); i++) {
        rb_ary_push(arr, CSTR2RVAL(gda_data_model_get_column_title(datamod, 
                                                                   i))); 
    }
    return arr;
}

/*
 * Method: each_column { |col_title| ... }
 *
 * Calls the block for each column title in the model, passing a reference
 * to a String object as parameter.
 *
 * Returns: always nil.
 */
static VALUE rb_gda_datamodel_each_column(self)
    VALUE self;
{
    rb_ary_each(rb_gda_datamodel_get_columns(self));
    return Qnil;
}

/*
 * Method: n_columns
 *
 * Returns: the number of columns in the model.
 */
static VALUE rb_gda_datamodel_get_n_columns(self)
    VALUE self;
{
    return INT2FIX(gda_data_model_get_n_columns(RGDA_DATAMODEL(self)));
}

/*
 * Method: get_column_title(colnum)
 * colnum: a column number.
 *
 * Returns: the title for the given column in the model.
 */
static VALUE rb_gda_datamodel_get_column(self, colnum)
    VALUE self, colnum;
{
    const gchar *column = gda_data_model_get_column_title(RGDA_DATAMODEL(self),  
                                                          FIX2INT(colnum));
    return column != NULL
        ? CSTR2RVAL(column) 
        : Qnil;
}

/*
 * Method: describe_column(colnum)
 * colnum: a column number.
 *
 * Queries the underlying data model implementation for a description of a
 * given column. That description is returned in the form of a 
 * Gda::FieldAttributes object, which contains all the information about the
 * given column in the data model.
 *
 * Returns: the description of the column, as a Gda::FieldAttributes object.
 */
static VALUE rb_gda_datamodel_describe_column(self, colnum)
    VALUE self, colnum;
{
#if defined(GDA_AT_LEAST_1_3)
    GdaColumn *a;
#else
    GdaFieldAttributes *a;
#endif
   
    a = gda_data_model_describe_column(RGDA_DATAMODEL(self),
                                       FIX2INT(colnum));

    return a != NULL
        ? RGDA_FIELD_ATTRIBUTES_NEW(a)
        : Qnil;
}

/*
 * Method: get_column_pos(col_title)
 * col_title: a column title.
 *
 * Gets the position of a column on the data model, based on the column's title.
 *
 * Returns: the position of the column in the data model, or -1 if the column
 * could not be found.
 */
static VALUE rb_gda_datamodel_get_column_pos(self, col_title)
    VALUE self, col_title;
{
    return INT2FIX(gda_data_model_get_column_position(RGDA_DATAMODEL(self),
                                                      RVAL2CSTR(col_title)));
}

/*
 * Method: get_value_at(colnum, rownum)
 * colnum: a column number.
 * rownum: a row number.
 *
 * Retrieves the data stored in the given position in the data model.
 * This is the main function for accessing data in a model.
 *
 * Returns: a Ruby object according to the type of the column is successful,
 * nil otherwise (out-of-bound position, etc...).
 */
static VALUE rb_gda_datamodel_get_value_at(self, colnum, rownum)
    VALUE self, colnum, rownum;
{
    const GdaValue *val = gda_data_model_get_value_at(RGDA_DATAMODEL(self),
                                                      FIX2INT(colnum),
                                                      FIX2INT(rownum));
    return val != NULL
        ? RGDA_VALUE_NEW(val)
        : Qnil;
}

/*
 * Method: rows
 *
 * Returns: a list of all the rows in the data model, as an Array of Gda::Row
 * objects.
 */
static VALUE rb_gda_datamodel_get_rows(self)
    VALUE self;
{
    GdaDataModel *datamod;
    VALUE arr;
    int i;

    arr = rb_ary_new();
    datamod = RGDA_DATAMODEL(self);
    for (i = 0; i < gda_data_model_get_n_rows(datamod); i++) {
        rb_ary_push(arr, RGDA_ROW_NEW(gda_data_model_get_row(datamod, 
                                                             i))); 
    }
    return arr;
}

/*
 * Method: each_row { |row| ... }
 *
 * Calls the block for each row in the data model, passing a reference to a
 * Gda::Row object as parameter.
 *
 * Returns: always nil.
 */ 
static VALUE rb_gda_datamodel_each_row(self)
    VALUE self;
{
    rb_ary_each(rb_gda_datamodel_get_rows(self));
    return Qnil;
}

/*
 * Method: n_rows
 *
 * Returns: the number of rows in the data model.
 */
static VALUE rb_gda_datamodel_get_n_rows(self)
    VALUE self;
{
    return INT2FIX(gda_data_model_get_n_rows(RGDA_DATAMODEL(self)));
}

/*
 * Method: get_row(rownum)
 * rownum: a row number.
 *
 * Retrieves a given row from the data model.
 *
 * Returns: the row, as a Gda::Row object, or nil if the given row number is
 * invalid.
 */
static VALUE rb_gda_datamodel_get_row(self, row_number)
    VALUE self, row_number;
{
    const GdaRow *row = gda_data_model_get_row(RGDA_DATAMODEL(self),  
                                               FIX2INT(row_number));
    return row != NULL
        ? RGDA_ROW_NEW(row)
        : Qnil;
}

/*
 * Method: append_row(*values)
 * values: a list of Gda::Value objects. Their length must match model's
 * column count.
 *
 * Appends a row to the data model.
 *
 * Returns: the added row, as a Gda::Row object, on success, nil on errors.
 */
static VALUE rb_gda_datamodel_append_row(self, values)
    VALUE self, values;
{
#if defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_append_row(RGDA_DATAMODEL(self), 
                                                RGDA_ROW(values)));
#else
    const GdaRow *row;
    GList *list = NULL;
    int i;
    
    for (i = 0; i < RARRAY_LEN(values); i++) {
        list = g_list_append(list, RGDA_VALUE(rb_ary_entry(values, i),
                                              GDA_VALUE_TYPE_NULL));
    }

    if (list == NULL) {
        rb_raise(rb_eArgError, "Wrong # of arguments (need at least 1)");
    }
    row = gda_data_model_append_row(RGDA_DATAMODEL(self), 
                                    (const GList *)list);
    return row != NULL 
        ? RGDA_ROW_NEW(row)
        : Qnil;
#endif
}

/*
 * Method: update_row(row)
 * row: a Gda::Row object.
 *
 * Updates a row data model. This results in the underlying database row's
 * values being changed.
 *
 * Returns: true if successful, false otherwise.
 */
static VALUE rb_gda_datamodel_update_row(self, row)
    VALUE self, row;
{
    return CBOOL2RVAL(gda_data_model_update_row(RGDA_DATAMODEL(self),
                                                RGDA_ROW(row)));
}

/*
 * Method: remove_row(row)
 * row: a Gda::Row object.
 *
 * Removes a row from the data model. This results in the underlying database
 * row being removed in the database.
 *
 * Returns: true if successful, false otherwise.
 */
static VALUE rb_gda_datamodel_remove_row(self, row)
    VALUE self, row;
{
    return CBOOL2RVAL(gda_data_model_remove_row(RGDA_DATAMODEL(self),
                                                RGDA_ROW(row)));
}

#if defined(GDA_AT_LEAST_1_1)
/*
 * Method: emit_column_inserted(colnum)
 * colnum: a column number.
 *
 * Emits the 'column_inserted' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_column_inserted(self, colnum)
    VALUE self, colnum;
{
    gda_data_model_column_inserted(RGDA_DATAMODEL(self), 
                                   FIX2INT(colnum));
    return self;
}

/*
 * Method: emit_column_updated(colnum)
 * colnum: a column number.
 *
 * Emits the 'column_updated' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_column_updated(self, colnum)
    VALUE self, colnum;
{
    gda_data_model_column_updated(RGDA_DATAMODEL(self),
                                  FIX2INT(colnum));
    return self;
}

/*
 * Method: emit_column_removed(colnum)
 * colnum: a column number.
 *
 * Emits the 'column_removed' and 'changed' signals on the model.
 *
 * Returns: self.
 */
static VALUE rb_gda_datamodel_column_removed(self, colnum)
    VALUE self, colnum;
{
    gda_data_model_column_removed(RGDA_DATAMODEL(self),
                                  FIX2INT(colnum));
    return self;
}

/*
 * Method: append_column(attributes)
 * attributes: a Gda::FieldAttributes object describing the column to add.
 *
 * Appends a column to the data model.
 *
 * Returns: true if successful, false otherwise.
 */
static VALUE rb_gda_datamodel_append_column(self, column)
    VALUE self, column;
{
    return CBOOL2RVAL(gda_data_model_append_column(RGDA_DATAMODEL(self),
                                                   RGDA_FIELD_ATTRIBUTES(column)));
}

/*
 * Method: update_column(column_id, attributes)
 * column_id: the number of the column to be updated.
 * attributes: a Gda::FieldAttributes object describing the column to update.
 *
 * Updates an existing column in the data model.
 *
 * Returns: true if successful, false otherwise.
 */
static VALUE rb_gda_datamodel_update_column(self, column_id, column)
    VALUE self, column_id, column;
{
    return CBOOL2RVAL(gda_data_model_update_column(RGDA_DATAMODEL(self),
                                                   FIX2INT(column_id),
                                                   RGDA_FIELD_ATTRIBUTES(column)));
}

/*
 * Method: remove_column(column_id)
 * column_id: the number of the column to be updated.
 *
 * Removes an existing column in the data model.
 *
 * Returns: true if successful, false otherwise.
 */
static VALUE rb_gda_datamodel_remove_column(self, column_id)
    VALUE self, column_id;
{
    return CBOOL2RVAL(gda_data_model_remove_column(RGDA_DATAMODEL(self),
                                                   FIX2INT(column_id)));
}
#endif /* GDA_AT_LEAST_1_1 */

/*
 * Method: updatable?
 *
 * Returns: true if the model can be updated, false otherwise.
 */
static VALUE rb_gda_datamodel_is_updatable(self)
    VALUE self;
{
#if defined(GDA_AT_LEAST_1_1) || defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_is_updatable(RGDA_DATAMODEL(self)));
#else
    return CBOOL2RVAL(gda_data_model_is_editable(RGDA_DATAMODEL(self)));
#endif
}

/*
 * Method: has_changed?
 *
 * Checks whether this data model is in updating mode or not. Updating
 * mode is set to true when Gda::DataModel#begin_update has been
 * called successfully, and is not set back to false until either
 * Gda::DataModel#cancel_update or Gda::DataModel#end_update have been called.
     
 * Returns: true if updating mode, false otherwise.
 */
static VALUE rb_gda_datamodel_has_changed(self)
    VALUE self;
{
#if defined(GDA_AT_LEAST_1_1) || defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_has_changed(RGDA_DATAMODEL(self)));
#else
    return CBOOL2RVAL(gda_data_model_is_editing(RGDA_DATAMODEL(self)));
#endif
}

/*
 * Method: begin_update
 *
 * Starts update of this data model. This method should be the
 * first called when modifying the data model.
 *
 * Returns: true on success, false if there was an error.
 */
static VALUE rb_gda_datamodel_begin_update(self)
    VALUE self;
{
#if defined(GDA_AT_LEAST_1_1) || defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_begin_update(RGDA_DATAMODEL(self)));
#else
    return CBOOL2RVAL(gda_data_model_begin_edit(RGDA_DATAMODEL(self)));
#endif
}

/*
 * Method: cancel_update
 *
 * Cancels update of this data model. This means that all changes
 * will be discarded, and the old data put back in the model.
 *
 * Returns: true on success, false if there was an error.
 */
static VALUE rb_gda_datamodel_cancel_update(self)
    VALUE self;
{
#if defined(GDA_AT_LEAST_1_1) || defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_cancel_update(RGDA_DATAMODEL(self)));
#else
    return CBOOL2RVAL(gda_data_model_cancel_edit(RGDA_DATAMODEL(self)));
#endif
}

/*
 * Method: end_update
 *
 * Approves all modifications and send them to the underlying
 * data source/store.
 *
 * Returns: true on success, false if there was an error.
 */
static VALUE rb_gda_datamodel_end_update(self)
    VALUE self;
{
#if defined(GDA_AT_LEAST_1_1)
    return CBOOL2RVAL(gda_data_model_end_update(RGDA_DATAMODEL(self)));
#else 
#  if defined(GDA_AT_LEAST_1_3)
    return CBOOL2RVAL(gda_data_model_commit_update(RGDA_DATAMODEL(self)));
#  else
    return CBOOL2RVAL(gda_data_model_end_edit(RGDA_DATAMODEL(self)));
#  endif
#endif
}

#if !defined(GDA_AT_LEAST_1_3)
/*
 * Method: to_comma_separated
 *
 * Converts the given model into a comma-separated series of rows.
 *
 * Returns: the string representation of the model.
 */
static VALUE rb_gda_datamodel_to_comma_separated(self)
    VALUE self;
{
    return CSTR2RVAL(gda_data_model_to_comma_separated(RGDA_DATAMODEL(self)));
}

/*
 * Method: to_tab_separated
 *
 * Converts the given model into a tab-separated series of rows.
 *
 * Returns: the string representation of the model.
 */
static VALUE rb_gda_datamodel_to_tab_separated(self)
    VALUE self;
{
    return CSTR2RVAL(gda_data_model_to_tab_separated(RGDA_DATAMODEL(self)));
}

/*
 * Method: to_xml(standalone=false)
 *
 * Converts the given model into a XML representation.
 *
 * Returns: the string representation of the model.
 */
static VALUE rb_gda_datamodel_to_xml(argc, argv, self)
    int argc;
    VALUE *argv, self;
{
    VALUE standalone;

    rb_scan_args(argc, argv, "01", &standalone);
    
    return CSTR2RVAL(gda_data_model_to_xml(RGDA_DATAMODEL(self), 
                                           NIL_P(standalone) ? FALSE : RVAL2CBOOL(standalone)));
}
#endif

/*
 * Method: command_text
 *
 * Gets the text of command that generated this data model.
 *
 * Returns: a string with the command issued.
 */
static VALUE rb_gda_datamodel_get_command_text(self)
    VALUE self;
{
    return CSTR2RVAL(gda_data_model_get_command_text(RGDA_DATAMODEL(self)));
}

/*
 * Method: set_command_text(text)
 * text: the command text.
 *
 * Sets the command text of this data model.
 *
 * Returns: self.
 */ 
static VALUE rb_gda_datamodel_set_command_text(self, text)
    VALUE self, text;
{
    gda_data_model_set_command_text(RGDA_DATAMODEL(self),
                                    RVAL2CSTR(text));
    return self;
}

/*
 * Method: command_type
 *
 * Returns: the command type of this data model (see Gda::Command::Type).
 */
static VALUE rb_gda_datamodel_get_command_type(self)
    VALUE self;
{
    return GENUM2RVAL(gda_data_model_get_command_type(RGDA_DATAMODEL(self)),
                      GDA_TYPE_COMMAND_TYPE);
}

/*
 * Method: set_command_type(type)
 * type: the command type (see Gda::Command::Type).
 *
 * Sets the command type of this data model.
 *
 * Returns: self.
 */ 
static VALUE rb_gda_datamodel_set_command_type(self, type)
    VALUE self, type;
{
    gda_data_model_set_command_type(RGDA_DATAMODEL(self),
                                    RVAL2GENUM(type, GDA_TYPE_COMMAND_TYPE));
    return self;
}

void Init_gda_datamodel(void) {
    VALUE c = G_DEF_CLASS(GDA_TYPE_DATA_MODEL, "DataModel", mGda);

    rb_define_method(c, "emit_changed",      rb_gda_datamodel_changed,      0); 
    rb_define_method(c, "emit_row_inserted", rb_gda_datamodel_row_inserted, 1); 
    rb_define_method(c, "emit_row_updated",  rb_gda_datamodel_row_updated,  1); 
    rb_define_method(c, "emit_row_removed",  rb_gda_datamodel_row_removed,  1); 
    rb_define_method(c, "freeze!", rb_gda_datamodel_freeze, 0);
    rb_define_method(c, "thaw!",   rb_gda_datamodel_thaw,   0);

    rb_define_method(c, "columns",          rb_gda_datamodel_get_columns,   0);
    rb_define_method(c, "each_column",      rb_gda_datamodel_each_column,   0);
    rb_define_method(c, "n_columns",        rb_gda_datamodel_get_n_columns, 0);
    rb_define_method(c, "get_column_title", rb_gda_datamodel_get_column,    1);

    rb_define_method(c, "describe_column",     rb_gda_datamodel_describe_column, 1);
    rb_define_method(c, "get_column_position", rb_gda_datamodel_get_column_pos,  1);
    rb_define_method(c, "get_value_at", rb_gda_datamodel_get_value_at, 2);
    
    rb_define_method(c, "rows",     rb_gda_datamodel_get_rows,   0);
    rb_define_method(c, "each_row", rb_gda_datamodel_each_row,   0);
    rb_define_method(c, "n_rows",   rb_gda_datamodel_get_n_rows, 0);
    rb_define_method(c, "get_row",  rb_gda_datamodel_get_row,    1);

    rb_define_method(c, "append_row", rb_gda_datamodel_append_row, -2);
    rb_define_method(c, "remove_row", rb_gda_datamodel_remove_row,  1);
    rb_define_method(c, "update_row", rb_gda_datamodel_update_row,  1);
   
    rb_define_method(c, "updatable?", rb_gda_datamodel_is_updatable, 0);
    rb_define_method(c, "changed?",  rb_gda_datamodel_has_changed,  0);
    
    rb_define_method(c, "begin_update",  rb_gda_datamodel_begin_update,  0);
    rb_define_method(c, "cancel_update", rb_gda_datamodel_cancel_update, 0);
    rb_define_method(c, "end_update",    rb_gda_datamodel_end_update,    0);

#if !defined(GDA_AT_LEAST_1_3)
    rb_define_method(c, "to_comma_separated", rb_gda_datamodel_to_comma_separated, 0);
    rb_define_method(c, "to_tab_separated",   rb_gda_datamodel_to_tab_separated,   0);
    rb_define_method(c, "to_xml",             rb_gda_datamodel_to_xml,            -1);
#endif

/*  TODO:
xmlNodePtr  gda_data_model_to_xml_node      (GdaDataModel *model,
                                             const gchar *name);
gboolean    gda_data_model_add_data_from_xml_node
                                            (GdaDataModel *model,
                                             xmlNodePtr node);
*/

    rb_define_method(c, "command_text", rb_gda_datamodel_get_command_text, 0);
    rb_define_method(c, "set_command_text", 
                     rb_gda_datamodel_set_command_text, 1);

    rb_define_method(c, "command_type", rb_gda_datamodel_get_command_type, 0);
    rb_define_method(c, "set_command_type", 
                     rb_gda_datamodel_set_command_type, 1);

#if defined(GDA_AT_LEAST_1_1)
    rb_define_method(c, "emit_column_inserted", rb_gda_datamodel_column_inserted, 1); 
    rb_define_method(c, "emit_column_updated",  rb_gda_datamodel_column_updated,  1); 
    rb_define_method(c, "emit_column_removed",  rb_gda_datamodel_column_removed,  1); 
    rb_define_method(c, "append_column", rb_gda_datamodel_append_column, 1);
    rb_define_method(c, "update_column", rb_gda_datamodel_update_column, 2);
    rb_define_method(c, "remove_column", rb_gda_datamodel_remove_column, 1);
#endif
    
    G_DEF_SETTERS(c);

    cGdaDataModel = c;
}

