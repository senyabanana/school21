#!/bin/bash

source system_info.sh

function system_save {
    source colors.sh
    colors
    echo -e "${bg_clr[0]}${t_clr[1]}HOSTNAME${reset}        = ${bg_clr[2]}${t_clr[3]}$HOSTNAME${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}TIMEZONE${reset}        = ${bg_clr[2]}${t_clr[3]}$TIMEZONE${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}USER${reset}            = ${bg_clr[2]}${t_clr[3]}$USER${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}OS${reset}              = ${bg_clr[2]}${t_clr[3]}$OS${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}DATE${reset}            = ${bg_clr[2]}${t_clr[3]}$DATE${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}UPTIME${reset}          = ${bg_clr[2]}${t_clr[3]}$UPTIME${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}UPTIME_SEC${reset}      = ${bg_clr[2]}${t_clr[3]}$UPTIME_SEC${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}IP${reset}              = ${bg_clr[2]}${t_clr[3]}$IP${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}MASK${reset}            = ${bg_clr[2]}${t_clr[3]}$MASK${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}GATEWAY${reset}         = ${bg_clr[2]}${t_clr[3]}$GATEWAY${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}RAM_TOTAL${reset}       = ${bg_clr[2]}${t_clr[3]}$RAM_TOTAL${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}RAM_USED${reset}        = ${bg_clr[2]}${t_clr[3]}$RAM_USED${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}RAM_FREE${reset}        = ${bg_clr[2]}${t_clr[3]}$RAM_FREE${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}SPACE_ROOT${reset}      = ${bg_clr[2]}${t_clr[3]}$SPACE_ROOT${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}SPACE_ROOT_USED${reset} = ${bg_clr[2]}${t_clr[3]}$SPACE_ROOT_USED${reset}"
    echo -e "${bg_clr[0]}${t_clr[1]}SPACE_ROOT_FREE${reset} = ${bg_clr[2]}${t_clr[3]}$SPACE_ROOT_FREE${reset}"
}

system_save