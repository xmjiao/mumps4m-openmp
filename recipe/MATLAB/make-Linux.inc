# make.inc for Linux with x86_64 version of MATLAB.
# We assume matlab, mex, and gfortran are in the path.

SYSTEM       = Linux
MACHINE      = x86_64

# On Linux and Mac, we assume gfortran is installed
MATLABROOT  := $(shell dirname $(shell dirname $(shell realpath `which matlab`)))
MEX          = mex
LIBFORT      = -lgfortran -L$(MATLABROOT)/sys/os/glnxa64 -liomp5

# Main MUMPS_DIR
topdir = ..
install_libdir = $(topdir)/../lib/$(SYSTEM)-$(MACHINE)
install_incdir = $(topdir)/../include

MUMPS_DIR = $(topdir)/..

# Orderings (see main Makefile.inc file from MUMPS)
LMETIS     = -L$(install_libdir) -lmetis
LPORD      = -L$(install_libdir) -lpord
LORDERINGS = $(LPORD) $(LMETIS)

# BLAS library:
LIBBLAS = -L$(install_libdir) -lopenblas

# extra options passed via mex command
OPTC    = -g -I$(install_incdir)
