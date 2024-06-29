#!/bin/bash

source catalog_info.sh

function catalog_save {
    green='\033[32m'
    black='\033[30m'
    reset='\033[0m'

    echo -e "${green}Total number of folders (including all nested ones)${reset} = $COUNT_FOLDERS"
    echo -e "${green}TOP 5 folders of maximum size arranged in descending order (path and size):${reset} $TOP_FOLDERS"
    echo -e "${green}Total number of files${reset} = $COUNT_FILES"
    echo -e "${green}Number of:${reset}"
    echo -e "${green}Configuration files (with the .conf extension)${reset} = $COUNT_CONF_FILES"
    echo -e "${green}Text files${reset} = $COUNT_TXT_FILES"
    echo -e "${green}Executable files${reset} = $COUNT_EXE_FILES"
    echo -e "${green}Log files (with the extension .log)${reset} = $COUNT_LOG_FILES"
    echo -e "${green}Archive files${reset} = $COUNT_ZIP_FILES"
    echo -e "${green}Symbolic links${reset} = $COUNT_SYM_LINKS"
    echo -e "${green}TOP 10 files of maximum size arranged in descending order (path, size and type):${reset} $TOP_FILES"
    echo -e "${green}TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):${reset} $TOP_EXE_FILES"

    PRINT_TIME=$(echo "$TIME" | sed 's/-/0/g')
    echo -e "${green}Script execution time (in seconds)${reset} = $PRINT_TIME ms"
}

catalog_save
