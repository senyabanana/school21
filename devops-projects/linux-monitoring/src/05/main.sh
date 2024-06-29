#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Error: script must be run with one parametr." >&2
elif [[ "${1: -1}" != "/" ]]; then
    echo "Error: Invalid path." >&2
elif [[ -d "$1" ]]; then
    output=$(echo $1 | tail -c 2)
    if [[ "$output" = "/" ]]; then
        export param=$1
        source catalog_info_out.sh
    fi
fi