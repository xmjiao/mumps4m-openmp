cp Makefile.inc MUMPS
cp src/Makefile MUMPS/src/Makefile
make -C MUMPS clean s
make -C MUMPS clean c
