#!/bin/bash

if [[ $# -eq 0 ]]; then
    echo "deb https://deb.goaccess.io/ $(lsb_release -cs) main" | sudo tee -a /etc/apt/sources.list.d/goaccess.list
    wget -O - https://deb.goaccess.io/gnugpg.key | sudo apt-key add -
    sudo apt-get update
    sudo apt-get install goaccess
    sudo goaccess --log-format=COMBINED ../04/*.log -a -o report.html
    if [[ -s report.html ]]; then
        echo -e "Data written to report.html"
    fi
else
    echo "Error"
fi