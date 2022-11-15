# It is possible to generate a MATLAB or an Octave interface thanks to
# the Octave MEX file compatibility. Comment/uncomment the lines below
# depending on whether you want to generate the MATLAB or the Octave
# interface

# To generate the MATLAB interface uncomment the following line
# ( the use of -largeArrayDims is necessary to work with sparse
# matrices since R2006b)
#MEX         = /opt/matlab/matlab/bin/mex -g -largeArrayDims
MEX          = mex -g -largeArrayDims LD=gfortran

# To generate the Octave interface uncomment the following line
# MEX         = mkoctfile -g --mex

# Main MUMPS_DIR
topdir = ..
SYSTEM = $(shell uname -s)
MACHINE = $(shell uname -m)
install_libdir = $(topdir)/../lib/$(SYSTEM)-$(MACHINE)
install_incdir = $(topdir)/../include

MUMPS_DIR = $(topdir)/..

# Orderings (see main Makefile.inc file from MUMPS)
LMETIS     = -L$(install_libdir) -lmetis
LPORD      = -L$(install_libdir) -lpord
LORDERINGS = $(LPORD) $(LMETIS)

# Fortran runtime library
# Please find out the path and name of your
# Fortran runtime, examples below:
# g95:
# LIBFORT = /usr/lib/libf95.a /usr/lib/libgcc.a
# Intel:
# LIBFORT = /opt/intel80/lib/libifcore.a /opt/intel80/lib/libifport.a /opt/intel80/lib/libirc.a
# PGI:
# LIBFORT = -L/usr/local/pgi/linux86/5.2/lib -llapack -lblas -lpgf90 -lpgc -lpgf90rtl -lpgftnrtl -lpgf902 -lpgf90_rpm1 -lpghpf2
# SGI 32-bit
# LIBFORT = -L/usr/lib32 -lblas -L/usr/lib32/mips4 -lfortran
# Sun
# LIBFORT = -L/opt2/SUNWspro7/lib -lsunperf -lfminvai -lfai2 -lfsu -lfmaxvai -lfmaxlai -lfai -lfsumai -lLIBFORT = /usr/local/lib/libgfortran.a

# gfortran
LIBFORT = -lgfortran -lgomp

# BLAS library:
# LIBBLAS = -L/usr/lib/atlas -lblas
# LIBBLAS = -lsunperf -lf77compat
# LIBBLAS = -lblas
LIBBLAS = -L$(install_libdir) -lopenblas
# LIBBLAS = /home/jylexcel/libs_courge/libblas.a  # -fPIC missing
# LIBBLAS = /usr/lib/libblas.so

# extra options passed via mex command
# Add -DINTSIZE64 if MUMPS was compiled with 64-bit integers (BLAS
# library should then have 64-bit integers as well)
OPTC    = -g -I$(install_incdir)
