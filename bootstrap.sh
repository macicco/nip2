#!/bin/sh

# set -x

# remove /everything/ ready to remake
rm -f Makefile Makefile.in aclocal.m4 config.* configure depcomp
rm -rf autom4te.cache
rm -f install-sh intltool-* ltmain.sh missing mkinstalldirs
rm -f src/*.o src/nip2 src/Makefile src/Makefile.in 

# exit

# some systems need libtoolize, some glibtoolize ... how annoying
echo testing for glibtoolize ...
if glibtoolize --version >/dev/null 2>&1; then 
  LIBTOOLIZE=glibtoolize
  echo using glibtoolize 
else 
  LIBTOOLIZE=libtoolize
  echo using libtoolize 
fi

aclocal 
glib-gettextize --force --copy
test -r aclocal.m4 && chmod u+w aclocal.m4
intltoolize --copy --force --automake
autoconf
autoheader
$LIBTOOLIZE --copy --force --automake
automake --add-missing --copy

