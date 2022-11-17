# make.inc for Mac with x86_64 version of MATLAB.
# We assume matlab, mex, and gfortran are in the path.

SYSTEM       = Darwin
MACHINE      = x86_64


MATLABROOT  := $(shell dirname $(shell dirname `which matlab`))
GCCROOT     := $(shell dirname $(shell dirname `which gfortran`))

MEX          = mex
LIBFORT      = -L$(GCCROOT)/lib -lgfortran -L$(MATLABROOT)/sys/os/maci64 -liomp5

# Main MUMPS_DIR
topdir = ..
install_libdir = $(topdir)/../lib/$(SYSTEM)-$(MACHINE)
install_incdir = $(topdir)/../include

MUMPS_DIR = $(topdir)/..

# Orderings (see main Makefile.inc file from MUMPS)
LMETIS     = -L$(install_libdir) -lmetis
LPORD      = -L$(install_libdir) -lpord
LORDERINGS = $(LPORD) $(LMETIS)

# OpenBLAS library
LIBBLAS = -L$(install_libdir) -lopenblas LDFLAGS='-Wl,-no_compact_unwind $$LDFLAGS'

# extra options passed via mex command
OPTC    = -g -I$(install_incdir)
