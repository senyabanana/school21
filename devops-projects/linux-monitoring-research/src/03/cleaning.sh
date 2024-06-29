#!/bin/bash

date="$(cat ../02/logfile.txt | awk -F'|' '{print $2}' | awk -F'_' '{print $3}')"
newDate=${date: -7} # создаем подстроку из последних 7 символов строки

function check_args {
    if [[ "$param1" -eq "1" ]]; then # очистка по лог-файлу
        file="$(cat ../02/logfile.txt | awk -F'|' '{print $2}')"
        for i in $file; do
            sudo rm -rf $i
            echo "${i}"
        done
        sudo rm -rf ../02/logfile.txt
        echo "logfile.txt was deleted"

    elif [[ "$param1" -eq "2" ]]; then # очистка по дате и времени создания
        echo "Input start time: YYYY-mm-DD HH:MM"
        read startDate
        echo "Input end time: YYYY-mm-DD HH:MM"
        read endDate
        # -newertm - новее чем, используется для поиска файлов, созданных между временем начала и концом
        # -not используется для исключения файлов, которые не соответствуют временному диапазону
        sudo bash -c "find / -newermt '$startDate' -not -newertm '$endDate' 2>/dev/null | xargs rm -r 2>/dev/null"
        sudo rm -rf ../02/logfile.txt
        echo "logfile.txt was deleted"
        
    elif [[ "$param1" -eq "3" ]]; then # очистка по маске имени
        echo "Input namemask: foldername_$newDate or filename.ext_$newDate"
        read nameMask
        find / -type f -name "*$nameMask*" 2>/dev/null | bash -c "sudo xargs rm -r 2>/dev/null"
        find / -type d -name "*$nameMask*" 2>/dev/null | bash -c "sudo xargs rm -r 2>/dev/null"
        echo "Folders and files deleted with namemask $nameMask"
        sudo rm -rf ../02/logfile.txt
        echo "logfile.txt was deleted"
    else
        # параметр введён неверно! Введите параметр от 1 до 3!
        echo "Error: parameter entered incorrectly! Enter a parameter from 1 to 3!"
    fi
}

check_args