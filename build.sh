#!/bin/bash

set -e

export SYSTEM=$(uname -s | cut -d'_' -f1)
export MACHINE=x86_64
export MUMPS_VERSION=5.3.4
export MUMPS_MAJOR_VERSION=$(echo ${MUMPS_VERSION} | cut -d'.' -f1)

OPENBLAS_VERSION=0.3.21
METIS_VERSION=5.1.0

MAKE=$([ "${SYSTEM}" = 'MINGW64' ] && echo 'mingw32-make' || echo 'make')
PREFIX=$(cd $(dirname "${BASH_SOURCE:-$0}") && pwd)

# Force to use x86_64 on Mac with Apple silicon
ARCH=$([ "${SYSTEM}" = 'Darwin' -a "$(uname -m)" = 'arm64' ] && echo 'arch -x86_64' || true)

build_openblas() {
    # Download and unpack
    curl -Ls https://github.com/xianyi/OpenBLAS/archive/v${OPENBLAS_VERSION}.tar.gz | tar zxf -
    cd OpenBLAS-${OPENBLAS_VERSION}

    USE_OPENMP=$([ "${SYSTEM}" = 'Darwin' ] && echo "" || echo "USE_OPENMP=1")
    NPROC=$([ "${SYSTEM}" = 'Darwin' ] && eval 'sysctl -n hw.physicalcpu' || nproc)
    # Build static library
    ${ARCH} make INTERFACE64=0 NO_LAPACKE=1 NO_CBLAS=1 NO_SHARED=1 ${USE_OPENMP} NUM_PARALLEL=${NPROC}

    # Copy static library
    mkdir -p "${PREFIX}/lib/${SYSTEM}-${MACHINE}"
    cp libopenblas.a "${PREFIX}/lib/${SYSTEM}-${MACHINE}"
    cd $PREFIX
}

build_metis() {
    # Download and unpack
    curl -Ls http://glaros.dtc.umn.edu/gkhome/fetch/sw/metis/metis-${METIS_VERSION}.tar.gz | tar zxf -
    cd metis-${METIS_VERSION}

    # Build METIS static library
    MACVER=$([ "${SYSTEM}" = 'Darwin' -a "$(uname -m)" = 'arm64' ] && echo 'CC=gcc CFLAGS=-mmacosx-version-min=10.15' || true)
    ${ARCH} ${MAKE} ${MACVER} config
    ${ARCH} ${MAKE}

    # Copy static library
    mkdir -p "${PREFIX}/lib/${SYSTEM}-${MACHINE}" "${PREFIX}/include"
    cp build/${SYSTEM}-x86_64/libmetis/libmetis.a "${PREFIX}/lib/${SYSTEM}-${MACHINE}"
    cp include/metis.h "${PREFIX}/include"
    cd $PREFIX
}

cp Makefile-${SYSTEM}.inc MUMPS/Makefile.inc
cp src/Makefile MUMPS/src/Makefile
cp libseq/Makefile MUMPS/libseq/Makefile
cp MATLAB/make.inc MUMPS/MATLAB/make.inc

# Build openblas
[ -f "$PREFIX/lib/${SYSTEM}-${MACHINE}/libopenblas.a" ] || build_openblas

# Build metis
[ -f "$PREFIX/include/metis.h" -a -f "$PREFIX/lib/${SYSTEM}-${MACHINE}/libmetis.a" ] || build_metis

# Build shared objects for single-precision real and complex arithemetic
${ARCH} ${MAKE} -C MUMPS/libseq clean
${ARCH} ${MAKE} -C MUMPS clean
${ARCH} ${MAKE} -C MUMPS s sexamples
(cd MUMPS/examples; ./ssimpletest < input_simpletest_real)
${ARCH} ${MAKE} -C MUMPS c cexamples
(cd MUMPS/examples; ./csimpletest < input_simpletest_cmplx)

# Build shared objects for double-precision real and complex arithemetic
${ARCH} ${MAKE} -C MUMPS d dexamples
(cd MUMPS/examples; ./dsimpletest < input_simpletest_real)
${ARCH} ${MAKE} -C MUMPS z zexamples
(cd MUMPS/examples; ./zsimpletest < input_simpletest_cmplx)

# Build MATLAB and run tests
${ARCH} ${MAKE} -C MUMPS/MATLAB clean d z
(cd MUMPS/MATLAB; matlab -nodisplay -batch 'simple_example; zsimple_example')