# make.inc for Linux with x86_64 version of MATLAB.
# We assume matlab is in the path, but not necessarily mex.

SYSTEM       = Linux
MACHINE      = x86_64

# On Linux and Mac, we assume gfortran is installed
MEX          = matlab -nojvm -batch 'mex
LIBFORT      = LDFLAGS="-fopenmp $$LDFLAGS" -lgfortran'

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
