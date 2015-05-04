bin_PROGRAMS = wacontrol

wacontrol_SOURCES = pch.cc \
WACApplication.cc \
appconfig.cc \
main.cc

wacontrol_LDADD = -lenutil -lennet

INCLUDES = -I$(top_srcdir)/enlibs/include/enutil \
           -I$(top_srcdir)/enlibs/include/ennet

AM_LDFLAGS = -L$(top_srcdir)/enlibs/lib

MAINTAINERCLEANFILES = Makefile.in
