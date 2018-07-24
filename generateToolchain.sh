#!/bin/bash



rm toolchain.mk
echo "CC=gcc" >> toolchain.mk
echo "LD=ld" >> toolchain.mk
echo "AS=gcc" >> toolchain.mk
echo "LIBPIP="$PWD"/libpip" >> toolchain.mk
echo "LIBFREERTOS="$PWD"/libfreertos" >> toolchain.mk
echo "LIBODSIDEMO="$PWD"/../lib_odsi_demo" >> toolchain.mk
mv toolchain.mk pipcore-mp/src/partitions/x86/
