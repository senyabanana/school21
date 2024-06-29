#!/bin/bash

export START=$(date +%s%N)
export TIME_START=$(date +%H:%M)

if [[ $# -eq 3 ]]; then
    export param1=$1
    export param2=$2
    export param3=$3

    sudo chmod +x ./clogging.sh
    ./clogging.sh
else
    echo "Error: Input 3 parametrs!"
fi