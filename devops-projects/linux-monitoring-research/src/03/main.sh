#!/bin/bash

if [[ $# -eq 1 ]]; then
    export param1=$1

    sudo chmod +x ./cleaning.sh
    ./cleaning.sh
else
    echo "Error: Input 1 parametrs!"
fi