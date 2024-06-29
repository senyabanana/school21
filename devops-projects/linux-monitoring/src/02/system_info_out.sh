#!/bin/bash

source source system_info.sh

function system_save {
    echo "HOSTNAME        = $HOSTNAME"
    echo "TIMEZONE        = $TIMEZONE"
    echo "USER            = $USER"
    echo "OS              = $OS"
    echo "DATE            = $DATE"
    echo "UPTIME          = $UPTIME"
    echo "UPTIME_SEC      = $UPTIME_SEC"
    echo "IP              = $IP"
    echo "MASK            = $MASK"
    echo "GATEWAY         = $GATEWAY"
    echo "RAM_TOTAL       = $RAM_TOTAL Gb"
    echo "RAM_USED        = $RAM_USED Gb"
    echo "RAM_FREE        = $RAM_FREE Gb"
    echo "SPACE_ROOT      = $SPACE_ROOT Mb"
    echo "SPACE_ROOT_USED = $SPACE_ROOT_USED Mb"
    echo "SPACE_ROOT_FREE = $SPACE_ROOT_FREE Mb"
}

system_save

read -p "Do you want to save the data to a file? [Y/n]" answer
if [[ $answer == [Yy] ]]; then
    file=$(date +"%d_%m_%Y_%H_%M_%S".status)
    system_save>$file
    echo "Data has been written to the file $(date '+%d_%m_%Y_%H_%M_%S').status"
else
    echo "Data has not been written to any file."
fi