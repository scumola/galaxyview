#!/bin/sh

aclocal -I m4
autoconf
automake -a
echo Done.
