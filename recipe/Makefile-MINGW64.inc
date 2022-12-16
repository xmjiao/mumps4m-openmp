#
#  This file is based on Make.inc/Makefile.debian.SEQ of MUMPS 5.3.4
#
# These settings for a PC with MATLAB and MINGW64 installed. METIS is built
# from source code. BLAS and LAPACK use a statically built libopenblas.a.



SYSTEM        = MINGW64
MACHINE       = x86_64
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
OPTF    = -O3 -fopenmp -DINTSIZE64 -fdefault-integer-8
OPTL    = -O3 -fopenmp
OPTC    = -O3 -fopenmp -DINTSIZE64
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
