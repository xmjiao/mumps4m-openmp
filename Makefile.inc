#
#  This file is part of MUMPS 5.3.4, released
#  on Mon Sep 28 07:16:41 UTC 2020
#
# These settings for a PC under Debian/linux with standard packages :
# metis (parmetis), scotch (ptscotch), openmpi, gfortran

# packages installation:
# apt-get install libmetis-dev libparmetis-dev libscotch-dev libptscotch-dev libatlas-base-dev openmpi-bin libopenmpi-dev liblapack-dev

# Begin orderings
LSCOTCHDIR = /usr/lib
ISCOTCH   = -I/usr/include/scotch

#LSCOTCH   = -L$(LSCOTCHDIR) -lptesmumps -lptscotch -lptscotcherr
LSCOTCH   = -L$(LSCOTCHDIR) -lesmumps -lscotch -lscotcherr

LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord

LMETISDIR = /usr/lib
#IMETIS    = -I/usr/include/parmetis
IMETIS    = -I/usr/include/metis

# LMETIS    = -L$(LMETISDIR) -lparmetis -lmetis
LMETIS    = -lmetis

# Corresponding variables reused later
#ORDERINGSF = -Dmetis -Dpord -Dparmetis -Dscotch -Dptscotch
ORDERINGSF = -Dmetis -Dpord -Dscotch -DINTSIZE64
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

ARGMISMATCH := $(if $(shell gfortran -c -fallow-argument-mismatch /dev/null -o /dev/null 2> /dev/null && echo true),-fallow-argument-mismatch -Wno-argument-mismatch)
FC = gfortran -fPIC $(ARGMISMATCH)
FL = gfortran -Wl,--no-undefined
AR = ar vr 
RANLIB = ranlib
#LAPACK = -llapack
MATLAB_ROOT = /usr/local/MATLAB/R2022a
LAPACK = -L$(MATLAB_ROOT)/bin/glnxa64 -lmwlapack


INCSEQ = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq

#LIBBLAS = -lblas
LIBBLAS = -lmwblas
LIBOTHERS = -lpthread

#Preprocessor defs for calling Fortran from C (-DAdd_ or -DAdd__ or -DUPPER)
CDEFS   = -DAdd_

#Begin Optimized options
OPTF    = -O -fopenmp
OPTL    = -O -fopenmp
OPTC    = -O -fopenmp
#End Optimized options

INCS = $(INCSEQ)
LIBS = -L$(libdir) -lmumps_common -lpord $(LMETIS) $(LIBSEQ) $(LSCOTCH) $(LAPACK) $(LIBBLAS)
LIBSEQNEEDED = libseqneeded
