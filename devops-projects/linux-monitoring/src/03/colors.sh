#!/bin/bash

function colors {
    clr[0]=$param1;
    clr[1]=$param2;
    clr[2]=$param3;
    clr[3]=$param4;

    for i in 0 1 2 3; do
        if [[ ${clr[$i]} < 1 || ${clr[$i]} > 6 ]]; then
            echo "There should be 4 parameters of number 1-6! Restart the script"
            exit 1
        fi
    done

    if [[ ${clr[0]} == ${clr[1]} || ${clr[2]} == ${clr[3]} ]]; then
        echo "The background and the color of the text cannot be the same! Restart the script"
        exit 1
    fi

    whiteBG="\033[107m";
    redBG="\033[41m";
    greenBG="\033[42m";
    blueBG="\033[44m";
    purpleBG="\033[45m";
    blackBG="\033[40m";

    whiteT="\033[97m";
    redT="\033[31m";
    greenT="\033[32m";
    blueT="\033[34m";
    purpleT="\033[35m";
    blackT="\033[30m";

    reset="\033[0m";

    for i in 0 2; do
        if [[ ${clr[$i]} == 1 ]]; then
            bg_clr[$i]=$whiteBG
        elif [[ ${clr[$i]} == 2 ]]; then
            bg_clr[$i]=$redBG
        elif [[ ${clr[$i]} == 3 ]]; then
            bg_clr[$i]=$greenBG
        elif [[ ${clr[$i]} == 4 ]]; then
            bg_clr[$i]=$blueBG
        elif [[ ${clr[$i]} == 5 ]]; then
            bg_clr[$i]=$purpleBG
        elif [[ ${clr[$i]} == 6 ]]; then
            bg_clr[$i]=$blackBG
        fi
    done

    for i in 1 3; do
        if [[ ${clr[$i]} == 1 ]]; then
            t_clr[$i]=$whiteT
        elif [[ ${clr[$i]} == 2 ]]; then
            t_clr[$i]=$redT
        elif [[ ${clr[$i]} == 3 ]]; then
            t_clr[$i]=$greenT
        elif [[ ${clr[$i]} == 4 ]]; then
            t_clr[$i]=$blueT
        elif [[ ${clr[$i]} == 5 ]]; then
            t_clr[$i]=$purpleT
        elif [[ ${clr[$i]} == 6 ]]; then
            t_clr[$i]=$blackT
        fi
    done
}

colors