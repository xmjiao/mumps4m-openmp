# It is possible to generate a MATLAB or an Octave interface thanks to
# the Octave MEX file compatibility. Comment/uncomment the lines below
# depending on whether you want to generate the MATLAB or the Octave
# interface

# To generate the MATLAB interface uncomment the following line
# ( the use of -largeArrayDims is necessary to work with sparse
# matrices since R2006b)
#MEX         = /opt/matlab/matlab/bin/mex -g -largeArrayDims

SYSTEM      := $(shell uname -s | cut -d'_' -f1)
MACHINE     := $(shell uname -m)

ifeq "$(SYSTEM)" "MINGW64"
MEX         := matlab -batch '"'mex
LIBFORT     := -L"$(shell cygpath $(shell dirname $(shell dirname `which GFORTRAN`))/lib/gcc/x86_64-w64-mingw32/6.3.0)" \
    -lgfortran -lquadmath LDFLAGS='-fopenmp $$LDFLAGS' '"'

else
MEX          = mex -g -largeArrayDims LD=gfortran
LIBFORT      = -lgfortan

endif

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
