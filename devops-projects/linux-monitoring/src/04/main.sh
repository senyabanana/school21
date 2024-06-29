#!/bin/bash

if [ $# -ne 0 ]; then
    echo "The script runs without parameters, restart the script!" >&2
else
    source system_info_out.sh
fi