require 'mkmf'
$LDFLAGS = ' ' + `pkg-config gobject-2.0 --libs`.chomp
$CFLAGS  = ' ' + `pkg-config gobject-2.0 --cflags`.chomp
$CFLAGS += ' -g'

src_dir = File.expand_path(File.join(File.dirname(__FILE__), 'src'))

Dir.mkdir('src') unless File.exist? 'src'
Dir.chdir "src"
begin
  create_makefile("glib2", src_dir)
ensure
  Dir.chdir('..')
end

File.open("Makefile", "w"){|mfile|
  if /mswin32/ =~ PLATFORM
    mfile.print "\

all:
		@cd src
		@nmake -nologo

install:
		@cd src
		@nmake -nologo install DESTDIR=$(DESTDIR)

site-install:
		@cd src
		@nmake -nologo site-install DESTDIR=$(DESTDIR)

clean:
		@cd src
		@nmake -nologo clean
		@cd ..
		@-rm -f Makefile extconf.h conftest.*
		@-rm -f glib2.lib *~
"
  else
    mfile.print "\

all:
		@cd src; make all

install:;	@cd src; make install
site-install:;	@cd src; make site-install
clean:
		@cd src; make clean
		@rm -f core glib2.a *~
distclean:	clean
		@cd src; make distclean
		@rm -f Makefile extconf.h conftest.*
		@rm -f core *~ mkmf.log
"
  end
}
