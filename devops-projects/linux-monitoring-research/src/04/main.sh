#!/bin/bash

if [[ $# -eq 0 ]]; then
    sudo chmod +x ./gen_nginx.sh
    ./gen_nginx.sh
else
    echo "Error: script runs without parametrs!"
fi