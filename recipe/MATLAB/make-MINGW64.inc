# make.inc for Windows with x86_64 version of MATLAB.
# We assume matlab is in the path, but not necessarily mex.
# In addition, mingw64-gcc has been installed and added into the path.

SYSTEM       = MINGW64
MACHINE      = x86_64

MEX          = matlab -nojvm -batch '"'mex
LIBFORT     := LD=gfortran LDFLAGS="-fopenmp $$LDFLAGS"

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
