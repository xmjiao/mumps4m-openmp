#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a Mac with Xcode command-line tools, gfortran, and MATLAB.
# The required system tools can be installed by setting up Miniconda3 and then
# run the command:
#
# conda install -c conda-forge gfortran cmake
#
# METIS is built from source code using 64-bit integer. BLAS and
# LAPACK use libmwblas and libmwlapack distributed with MATLAB, which
# is based on MKL with 64-bit integers. MATLAB is found by using the
# realpath of the `matlab` command in the path.
#
# Note that OpenMP is disabled.

# Begin orderings
LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord

LMETISDIR = $(topdir)/../lib/$(SYSTEM)
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
DLLEXT  = .dylib
OUTC    = -o
OUTF    = -o
RM = /bin/rm -f
CC = gcc -mmacosx-version-min=10.15 -fPIC

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch)
FC = gfortran -mmacosx-version-min=10.15 -fPIC $(ARGMISMATCH)
FL = gfortran -mmacosx-version-min=10.15
FLFLAGS = -shared
AR = ar vr 
RANLIB = ranlib

MATLAB_LIBDIR := $(shell dirname $(realpath /usr/local/bin/matlab))/maci64
LAPACK = -L$(MATLAB_LIBDIR) -Wl,-rpath $(MATLAB_LIBDIR) -lmwlapack


INCSEQ = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq

#LIBBLAS = -lblas
LIBBLAS = -lmwblas
LIBOTHERS = -lpthread

#Preprocessor defs for calling Fortran from C (-DAdd_ or -DAdd__ or -DUPPER)
CDEFS   = -DAdd_

#Begin Optimized options
OPTF    = -O3 -fdefault-integer-8
OPTL    = -O3
OPTC    = -O3 -DINTSIZE64 -DPORD_INTSIZE64
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
