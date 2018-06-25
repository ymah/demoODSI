#!/bin/bash




function updateGitFreeRTOS(){

    cd src/partitions/x86/pip-freertos

    git pull origin master

    cd -
}



function updateGitLibFreeRTOS(){

    cd ../libfreertos/ 
    git pull origin master
    cd -
}


updateGitLibFreeRTOS
updateGitFreeRTOS
