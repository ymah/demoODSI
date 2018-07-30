#!/bin/bash

./generateToolchain.sh


generateToolChain()

if [ "$1" == "galileo" ]
then
   echo "Compiling for Galileo Gen 2"
else
    echo "Compiling for x86_multiboot"
fi



if [ "$1" == "galileo" ]
then
    make -C libpip/ VARIANT=galileo clean all || exit
else
    make -C libpip/ clean all || exit
fi

make -C libfreertos clean all || exit

echo "Owner" && sleep 1
make -C pipcore-mp/src/partitions/x86/owner/ all || exit
echo "sp1" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp1Task/ all || exit
echo "sp2" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp2Task/ all || exit
echo "sp3" && sleep 1
make -C pipcore-mp/src/partitions/x86/sp3Task/ all || exit
echo "Network manager" && sleep 1
make -C pipcore-mp/src/partitions/x86/NetworkMngr/ all || exit
echo "Compilation des sous partition terminée" && sleep 1

yes | cp pipcore-mp/src/partitions/x86/owner/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part1.bin
yes | cp pipcore-mp/src/partitions/x86/sp1Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part2.bin
yes | cp pipcore-mp/src/partitions/x86/sp2Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part3.bin
yes | cp pipcore-mp/src/partitions/x86/sp3Task/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part4.bin
yes | cp pipcore-mp/src/partitions/x86/NetworkMngr/pip-freertos.bin pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/Support_Files/partitions_images/part5.bin


#make -C pipcore-mp/src/partitions/x86/pip-freertos/Demo/pip-kernel/ clean all
make -B -C pipcore-mp/src/partitions/x86/pip-freertos/ all || exit

if [ "$1" == "galileo" ]
then
    make -C pipcore-mp TARGET=galileo PARTITION=pip-freertos clean partition kernel || exit
else
    make -C pipcore-mp TARGET=x86_multiboot PARTITION=pip-freertos clean partition kernel || exit
fi
