#!/bin/bash

if [[ "$param1" -eq "1" ]]; then # Все записи, отсортированные по коду ответа
    for (( i = 1; i <6; i++ )); do
        sort -k 9 ../04/$i.log -o sort$i.log
        cat sort$i.log
    done
elif [[ "$param1" -eq "2" ]]; then # Все уникальные IP, встречающиеся в записях
    for (( i = 1; i <6; i++ )); do
        awk '{print $1}' ../04/$i.log > sort$i.log
        cat sort$i.log
    done
elif [[ "$param1" -eq "3" ]]; then # Все запросы с ошибками (код ответа - 4хх или 5хх)
    for (( i = 1; i <6; i++ )); do
        awk '$9 ~ /[45]/' ../04/$i.log > sort$i.log
        cat sort$i.log
    done
elif [[ "$param1" -eq "4" ]]; then # Все уникальные IP, которые встречаются среди ошибочных запросов
    for (( i = 1; i <6; i++ )); do
        awk '$9 ~ /[45]/' ../04/$i.log > temp.log
        awk '{print $1}' temp.log > sort$i.log
        sudo rm -rf temp.log
        cat sort$i.log
    done
else
    echo "Error ${param1}: use parameters between 1 - 4!"
    exit
fi