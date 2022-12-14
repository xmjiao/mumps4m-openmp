#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.5.1
#
# These settings for a PC under Debian/linux with gfortran.
# The required system tools can be installed by installed using the command:
#
# sudo apt install gfortran cmake
#
# BLAS and LAPACK use a statically built libopenblas.a to avoid MATLAB
# overriding the LAPACK and BLAS routines.

SYSTEM   = Linux
MACHINE  = x86_64
MUMPS_VERSION = 5.5.1

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
CC = gcc -fPIC

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch)
FC = gfortran -fPIC $(ARGMISMATCH)
FL = gfortran

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
OPTF    = -O3 -fopenmp
OPTL    = -O3 -fopenmp
OPTC    = -O3 -fopenmp
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
