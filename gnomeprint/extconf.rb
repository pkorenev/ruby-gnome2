=begin
extconf.rb for Ruby/GnomePrint extention library
=end
PACKAGE_NAME = "gnomeprint2"

TOPDIR = File.expand_path(File.dirname(__FILE__) + '/..')
MKMF_GNOME2_DIR = TOPDIR + '/glib/src/lib'
SRCDIR = TOPDIR + '/gnomeprint/src'

$LOAD_PATH.unshift MKMF_GNOME2_DIR

require 'mkmf-gnome2'
modname = "libgnomeprint-2.2"
app_name = "LIBGNOMEPRINT"

PKGConfig.have_package(modname, 2, 8) or exit 1
setup_win32(PACKAGE_NAME)

add_depend_package("glib2", "glib/src", TOPDIR)
add_depend_package("libart2", "libart/src", TOPDIR)

make_version_header(app_name, modname)

create_makefile_at_srcdir(PACKAGE_NAME, SRCDIR, "-DRUBY_GNOMEPRINT2_COMPILATION")
create_top_makefile
