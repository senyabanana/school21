#!/bin/bash

if [ $# -ne 4 ]; then
    echo "There should be 4 parameters, restart the script!"
else
    export param1=$1
    export param2=$2
    export param3=$3
    export param4=$4
    source system_info_out.sh
fi