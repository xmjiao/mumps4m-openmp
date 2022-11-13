#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a PC under Debian/linux with MATLAB and gfortran.
# METIS will be built from source code using 64-bit integer. BLAS and
# LAPACK use libmwblas and libmwlapack distributed with MATLAB, which
# is based on MKL with 64-bit integers. MATLAB is assumed to be installed
# at /usr/local/MATLAB/<Release>. If multiple MATLAB versions are installed,
# then the newest version will be used.

# Begin orderings
LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord

LMETISDIR = $(topdir)/../lib
IMETIS    = -I$(topdir)/../include
LMETIS    = -lmetis

# Corresponding variables reused later
ORDERINGSF = -Dmetis -Dpord
ORDERINGSC  = $(ORDERINGSF)

LORDERINGS = $(LMETIS) $(LPORD) $(LSCOTCH)
IORDERINGSF = $(ISCOTCH)
IORDERINGSC = $(IMETIS) $(IPORD) $(ISCOTCH)
# End orderings
################################################################################

PLAT    =
LIBEXT  = .a
DLLEXT  = .so
OUTC    = -o
OUTF    = -o
RM = /bin/rm -f
CC = gcc -fPIC

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch)
FC = gfortran -fPIC $(ARGMISMATCH)
FL = gfortran
FLFLAGS = -shared -Wl,--no-undefined

AR = ar vr 
RANLIB = ranlib
#LAPACK = -llapack

MATLAB_VERSION := $(shell ls -r /usr/local/MATLAB/ | cut -d/ -f1)
MATLAB_ROOT := /usr/local/MATLAB/$(MATLAB_VERSION)
LAPACK = -L$(MATLAB_ROOT)/bin/glnxa64 -Wl,-rpath=/usr/local/MATLAB/$(MATLAB_VERSION)/bin/glnxa64 -lmwlapack


INCSEQ = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq

#LIBBLAS = -lblas
LIBBLAS = -lmwblas
LIBOTHERS = -lpthread

#Preprocessor defs for calling Fortran from C (-DAdd_ or -DAdd__ or -DUPPER)
CDEFS   = -DAdd_

#Begin Optimized options
OPTF    = -O3 -fopenmp -fdefault-integer-8
OPTL    = -O3 -fopenmp 
OPTC    = -O3 -fopenmp -DINTSIZE64 -DPORD_INTSIZE64
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
