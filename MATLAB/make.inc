SYSTEM      := $(shell uname -s | cut -d'_' -f1)
MACHINE     := $(shell uname -m)

ifeq "$(SYSTEM)" "MINGW64"
# On Windows, we assume MINGW64 gcc and gfortran are installed
MEX         := matlab -batch '"'mex
LIBFORT     := -L"$(shell dirname $(shell dirname `which gcc`))/lib/gcc/x86_64-w64-mingw32/6.3.0" \
    -lgfortran -lquadmath LDFLAGS="-fopenmp $$LDFLAGS"

else
# On Linux and Mac, we assume gfortran is installed
MEX          = matlab -batch 'mex LD=gfortran
LIBFORT      = LDFLAGS="-fopenmp $$LDFLAGS" -lgfortran'
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
