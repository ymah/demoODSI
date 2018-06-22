#!/bin/bash

if [ "$1" == "galileo" ]
then
   echo "Compiling for Galileo Gen 2"
else
    echo "Compiling for x86_multiboot"
fi



if [ "$1" == "galileo" ]
then
    make -C ../libpip/ VARIANT=galileo clean all
else
    make -C ../libpip/ clean all
fi


echo "Owner" && sleep 1
make -C src/partitions/x86/owner/ all
echo "sp1" && sleep 1
make -C src/partitions/x86/sp1Task/ all
echo "sp2" && sleep 1
make -C src/partitions/x86/sp2Task/ all
echo "sp3" && sleep 1
make -C src/partitions/x86/sp3Task/ all
echo "Network manager" && sleep 1
make -C src/partitions/x86/NetworkMngr/ all
echo "Compilation des sous partition terminée" && sleep 1

yes | cp src/partitions/x86/owner/pip-freertos.bin src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part1.bin
yes | cp src/partitions/x86/sp1Task/pip-freertos.bin src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part2.bin
yes | cp src/partitions/x86/sp2Task/pip-freertos.bin src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part3.bin
yes | cp src/partitions/x86/sp3Task/pip-freertos.bin src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part4.bin
yes | cp src/partitions/x86/NetworkMngr/pip-freertos.bin src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part5.bin


#make -C src/partitions/x86/pip-freertos/Demo/pip-kernel/ clean all
make -B -C src/partitions/x86/pip-freertos/ all

if [ "$1" == "galileo" ]
then
    make TARGET=galileo PARTITION=pip-freertos clean partition kernel
else
    make TARGET=x86_multiboot PARTITION=pip-freertos clean partition kernel
fi
