#!/bin/bash

if [ "$1" == "galileo" ]
then
   echo "Compiling for Galileo Gen 2"
else
    echo "Compiling for x86_multiboot"
fi



if [ "$1" == "galileo" ]
then
    make -C libpip/ VARIANT=galileo clean clean
else
    make -C libpip/ clean clean
fi


echo "Owner" && sleep 1
make -C pipcore-mp/src/partitions/x86/owner/ clean
echo "sp1" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp1Task/ clean
echo "sp2" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp2Task/ clean
echo "sp3" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp3Task/ clean
echo "Network manager" && sleep 1
make -C pipcore-mp/src/partitions/x86/NetworkMngr/ clean
echo "Compilation des sous partition terminée" && sleep 1

yes | cp pipcore-mp/src/partitions/x86/owner/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part1.bin
yes | cp pipcore-mp/src/partitions/x86/sp1Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part2.bin
yes | cp pipcore-mp/src/partitions/x86/sp2Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part3.bin
yes | cp pipcore-mp/src/partitions/x86/sp3Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part4.bin
yes | cp pipcore-mp/src/partitions/x86/NetworkMngr/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part5.bin


#make -C pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/ clean clean
make -B -C pipcore-mp/src/partitions/x86/pip-freertos/ clean

make -C pipcore-mp mrproper

make -C libfreertos clean
