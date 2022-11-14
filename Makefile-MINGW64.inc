#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a PC with MATLAB and MINGW64 installed. BLAS and
# LAPACK use those distributed with Anaconda or Miniconda. The required
# system tools can be installed by running the command:
#
# conda install -c conda-forge mumps_seq
#
# Note that mumps_seq in conda-forge is an older version, and OpenMP was not
# enabled. libmumps builds a newer version with OpenMP enabled. METIS is built
# from source code.


SYSTEM        = MINGW64
MACHINE       = x86_64
MUMPS_VERSION = 5.3.4

# Begin orderings
LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord

LMETISDIR = $(topdir)/../lib/$(SYSTEM)-$(MACHINE)
IMETIS    = -I$(topdir)/../include/$(SYSTEM)-$(MACHINE)
LMETIS    = -L$(LMETISDIR) -lmetis

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
DLLEXT  = .dll
OUTC    = -o 
OUTF    = -o 
RM = /bin/rm -f
CC = gcc -fPIC

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch)
FC = gfortran -fPIC $(ARGMISMATCH)
FL = gfortran
FLFLAGS = -shared
AR = ar vr 
RANLIB = ranlib

CONDA_PREFIX := $(shell cygpath $(CONDA_PREFIX))

LAPACK = -L"$(CONDA_PREFIX)"/Library/bin/ -lliblapack

LIBBLAS = -llibblas
LIBOTHERS = -lpthread

INCSEQ = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq

#Preprocessor defs for calling Fortran from C (-DAdd_ or -DAdd__ or -DUPPER)
CDEFS   = -DAdd_

#Begin Optimized options
OPTF    = -O3 -fopenmp
OPTL    = -O3 -fopenmp
OPTC    = -O3 -fopenmp
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
