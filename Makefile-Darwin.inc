#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a Mac with Xcode command-line tools and gfortran.
# The required system tools can be installed by setting up the x86_64
# version of Miniconda3 (or Anaconda3) and then run the command:
#
# conda install -c conda-forge gfortran cmake
#
# METIS is built from source code. BLAS and LAPACK use a statically
# built version without OpenMP.

SYSTEM   = Darwin
MACHINE  = x86_64
MUMPS_VERSION = 5.3.4

SYSLIBDIR = $(topdir)/../lib/$(SYSTEM)-$(MACHINE)

# Begin orderings
LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord

LMETISDIR = $(SYSLIBDIR)
IMETIS    = -I$(topdir)/../include
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
OUTC    = -o 
OUTF    = -o 
RM = /bin/rm -f
CC = gcc -mmacosx-version-min=10.15 -fPIC

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch)
FC = gfortran -mmacosx-version-min=10.15 -fPIC $(ARGMISMATCH)
FL = gfortran -mmacosx-version-min=10.15
AR = ar vr 
RANLIB = ranlib

LAPACK = -L$(SYSLIBDIR) -lopenblas
LIBBLAS =
LIBOTHERS = -lpthread

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
