#!/bin/bash
if [ "$1" == "galileo" ]
then
   echo "Compiling for Galileo Gen 2"
else
    echo "Compiling for x86_multiboot"
fi



if [ "$1" == "galileo" ]
then
    make -C libpip/ VARIANT=galileo clean all
else
    make -C libpip/ clean all
fi

make -C pipcore-mp/src/partitions/x86/testServices/ clean all
yes | cp pipcore-mp/src/partitions/x86/testServices/testServices.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part1.bin
yes | cp pipcore-mp/src/partitions/x86/testServices/testServices.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part2.bin
yes | cp pipcore-mp/src/partitions/x86/testServices/testServices.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part3.bin
yes | cp pipcore-mp/src/partitions/x86/testServices/testServices.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part4.bin
yes | cp pipcore-mp/src/partitions/x86/testServices/testServices.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part5.bin




#make -C pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/ clean all
make -C pipcore-mp/src/partitions/x86/pip-freertos/ clean all

if [ "$1" == "galileo" ]
then
    make -C pipcore-mp TARGET=galileo PARTITION=pip-freertos clean partition kernel
else
    make -C pipcore-mp TARGET=x86_multiboot PARTITION=pip-freertos clean partition kernel
fi
