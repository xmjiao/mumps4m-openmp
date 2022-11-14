#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a Mac with Xcode command-line tools and gfortran.
# The required system tools can be installed by setting up Miniconda3 and then
# run the command:
#
# conda install -c conda-forge gfortran cmake
#
# METIS is built from source code. BLAS and LAPACK use those distributed
# with MATLAB. OpenMP is not supported.

SYSTEM   = Darwin
MACHINE  = x86_64
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

LAPACK = -llapack

LIBBLAS = -lblas
LIBOTHERS = -lpthread

MATLABROOT = $(shell realpath `which matlab`/../..)
INCSEQ = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq

#Preprocessor defs for calling Fortran from C (-DAdd_ or -DAdd__ or -DUPPER)
CDEFS   = -DAdd_

#Begin Optimized options
OPTF    = -O3
OPTL    = -O3
OPTC    = -O3
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
