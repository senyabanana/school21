#!/bin/bash

chmod +x ./info.sh

if [[ $# -ne 0 ]]; then
    echo "Error, script runs without parameters!"
else
    while sleep 3; do
        ./info.sh > my_metrics.html
    done
fi