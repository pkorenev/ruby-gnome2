/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/**********************************************************************

  rbglib.h -

  $Author: mutoh $
  $Date: 2004/03/05 15:50:31 $

  Copyright (C) 2002-2004  Ruby-GNOME2 Project
  Copyright (C) 2002,2003  Masahiro Sakai

**********************************************************************/

#include <glib.h>
#include "ruby.h"

#ifndef __RBGLIB_H__
#define __RBGLIB_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define RBGLIB_MAJOR_VERSION 0
#define RBGLIB_MINOR_VERSION 9
#define RBGLIB_MICRO_VERSION 0

#ifndef StringValue
#define StringValue(s) ((s) = (TYPE(s) == T_STRING) ? (s) : rb_str_to_str(s))
#endif
#ifndef SafeStringValue
#define SafeStringValue(v) rb_check_safe_str(StringValue(v))
#endif
#ifndef StringValuePtr
#define StringValuePtr(v) rbg_string_value_ptr(&(v))
#endif

#ifndef LONG2NUM
#define LONG2NUM INT2NUM
#endif

#ifndef ULONG2NUM
#define ULONG2NUM UINT2NUM
#endif

#define RVAL2CSTR(v) (StringValuePtr(v))
#define CSTR2RVAL(s) (rbg_cstr2rval(s))

#define CBOOL2RVAL(b)   ((b) ? Qtrue : Qfalse)
#define RVAL2CBOOL(b)   (RTEST(b))

#if defined(G_PLATFORM_WIN32) && !defined(RUBY_GLIB2_STATIC_COMPILATION)
#  ifdef RUBY_GLIB2_COMPILATION
#    define RUBY_GLIB2_VAR __declspec(dllexport)
#  else
#    define RUBY_GLIB2_VAR extern __declspec(dllimport)
#  endif
#else
#  define RUBY_GLIB2_VAR extern
#endif

RUBY_GLIB2_VAR VALUE mGLib;
extern gchar* rbg_string_value_ptr(volatile VALUE* ptr);
extern VALUE rbg_cstr2rval(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RBGLIB_H__ */
