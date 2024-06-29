#!/bin/bash

if [ ! -f "config.conf" ]; then
    echo "Config file not found!" >&2
    exit 1
fi

function colors {
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

    countParam=0
    countErr=0

    for var in "column1_background" "column1_font_color" "column2_background" "column2_font_color"
    do
        if [[ $(grep -c $var config.conf) -eq 1 ]]; then
            countParam=$(($countParam + 1))
        fi
    done

    if [[ $countParam -eq 4 ]]; then
        clr[0]=$(grep column1_background config.conf | awk -F = '{printf("%i", $2)}');
        clr[1]=$(grep column1_font_color config.conf | awk -F = '{printf("%i", $2)}');
        clr[2]=$(grep column2_background config.conf | awk -F = '{printf("%i", $2)}');
        clr[3]=$(grep column2_font_color config.conf | awk -F = '{printf("%i", $2)}');
    else
        countErr=$(($countErr + 1))
    fi

    if [[ $countErr -gt 0 ]]; then
        echo "Invalid config! All parameters are set by default" >&2
        clr[0]=3;
        clr[1]=6;
        clr[2]=4;
        clr[3]=1;
    fi

    for i in 0 1 2 3; do
        if [[ ${clr[$i]} == 1 ]]; then
            color[$i]="(white)"
        elif [[ ${clr[$i]} == 2 ]]; then
            color[$i]="(red)"
        elif [[ ${clr[$i]} == 3 ]]; then
            color[$i]="(green)"
        elif [[ ${clr[$i]} == 4 ]]; then
            color[$i]="(blue)"
        elif [[ ${clr[$i]} == 5 ]]; then
            color[$i]="(purple)"
        elif [[ ${clr[$i]} == 6 ]]; then
            color[$i]="(black)"
        fi
    done

    for i in 0 1 2 3; do
        if [[ ${clr[$i]} < 1 || ${clr[$i]} > 6 ]]; then
            echo "There should be 4 parameters of number 1-6! Incorrect config" >&2
            exit 1
        fi
    done

    if [[ ${clr[0]} == ${clr[1]} || ${clr[2]} == ${clr[3]} ]]; then
        echo "The background and the color of the text cannot be the same! Incorrect config" >&2
        exit 1
    fi

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