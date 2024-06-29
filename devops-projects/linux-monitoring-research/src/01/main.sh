#!/bin/bash

if [[ $# -eq 6 ]]; then
    export param1=$1
    export param2=$2
    export param3=$3
    export param4=$4
    export param5=$5
    export param6=$6

    sudo chmod +x ./generation.sh
    ./generation.sh
else
    echo "Error: Input 7 parametrs!"
fi