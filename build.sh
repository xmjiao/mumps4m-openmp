#!/bin/bash

set -e

export SYSTEM=$(uname -s | cut -d'_' -f1)
export MACHINE=x86_64

METIS_VERSION=5.1.0
export MUMPS_VERSION=5.3.4
export MUMPS_MAJOR_VERSION=$(echo ${MUMPS_VERSION} | cut -d'.' -f1)
MAKE=$([ "${SYSTEM}" = 'MINGW64' ] && echo 'mingw32-make' || echo 'make')
PREFIX=$(cd $(dirname "${BASH_SOURCE:-$0}") && pwd)

# Force to use x86_64 on Mac with Apple silicon
ARCH=$([ "${SYSTEM}" = 'Darwin' -a "$(uname -m)" = 'arm64' ] && echo 'arch -x86_64' || true)

build_metis_64() {
    # Download and unpack
    curl -s -L http://glaros.dtc.umn.edu/gkhome/fetch/sw/metis/metis-${METIS_VERSION}.tar.gz | tar zxf -
    cd metis-${METIS_VERSION}

    # Build METIS static library
    if [ "${SYSTEM}" = "Linux" ]; then
        perl -e 's/#define IDXTYPEWIDTH 32/#define IDXTYPEWIDTH 64/g' -pi include/metis.h
    else
        perl -e 's/#define IDXTYPEWIDTH 64/#define IDXTYPEWIDTH 32/g' -pi include/metis.h
    fi
    ${ARCH} ${MAKE} config
    ${ARCH} ${MAKE}

    # Copy header and static library
    mkdir -p "${PREFIX}/lib/${SYSTEM}-${MACHINE}" "${PREFIX}/include/${SYSTEM}-${MACHINE}"
    cp build/${SYSTEM}-x86_64/libmetis/libmetis.a "${PREFIX}/lib/${SYSTEM}-${MACHINE}"
    cp include/metis.h "${PREFIX}/include/${SYSTEM}-${MACHINE}"
    cd $PREFIX
}

cp Makefile-${SYSTEM}.inc MUMPS/Makefile.inc
cp src/Makefile MUMPS/src/Makefile

# Build metis with 64-bit integer
[ -f "$PREFIX/include/${SYSTEM}-${MACHINE}/metis.h" -a -f "$PREFIX/lib/${SYSTEM}-${MACHINE}/libmetis.a" ] || build_metis_64

# Build shared objects for single-precision real and complex arithemetic
${ARCH} ${MAKE} -C MUMPS clean
${ARCH} ${MAKE} -C MUMPS s sexamples
(cd MUMPS/examples; ./ssimpletest < input_simpletest_real)
${ARCH} ${MAKE} -C MUMPS c cexamples
(cd MUMPS/examples; ./csimpletest < input_simpletest_cmplx)
