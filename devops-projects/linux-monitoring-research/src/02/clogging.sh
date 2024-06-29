#!/bin/bash

inputFile="logfile.txt"
sudo touch $inputFile

function check_args {
    if [[ ${#param1} -gt 7 ]]; then
        # в названии папок должно быть не более 7 знаков
        echo "Error {$param1}: folder names must contain mo more than 7 characters!"
        exit 1
    fi

    if [[ $param1 =~ [^A-Za-z] ]]; then
        # используется только английский алфавит
        echo "Error {$param1}: only letters of the English alphabet!"
        exit 1
    fi

    if [[ ! "$param2" =~ ^([A-Za-z]{1,7}).([A-Za-z]{1,3})$ ]]; then
        # для имени файла - не более 7 знаков, для расширения - не более 3 знаков
        echo "Error {$param2}: for the file name - no more than 7 characters, for the extension - no more than 3 characters!"
        exit 1
    fi

    export filesize=$(echo $param3 | awk -F"Mb" '{print $1}')
    if [[ !($param3 =~ Mb$) || ($filesize =~ [^0-9]) || ($filesize -gt 100) || ($filesize -le 0) ]]; then
        # формат размера файла введен некорректно
        echo "Error {$param3}: the file size format is entered incorrectly!"
        exit 1
    fi
}

function folders_and_files {
    folder=$param1 # имя начальной папки
    folderRandom="$(compgen -d / | shuf -n1)" # генерируем случайный каталог, затем выбираем один рандомом
    filename=$(echo $param2 | awk -F. '{print $1}') # имя файла
    fileExtension=$(echo $param2 | awk -F. '{print $2}') # расширение файла
    lastCharNameFolder=${param1: -1} # последний символ из имени начальной папки
    saveName=$fileName # сохраняет исходное имя файла
    lastCharFileName=${fileName: -1} # последний символ из имени файла
    logDate="$(date +"%d%m%y")" # текущая дата для созданных файлов и папок
    newDate="DATE = $(date +"%d.%m.%y")" # форматированная строка с текущей датой для записи в лог

    countDir=$(( $RANDOM % 100 + 1 )) # генерируем случайное колличество дирректорий

    # если имя начальной папки имеет длину менее 5 символов, то к нему добавляются символы из переменной
    # до достижения длины в 5 символа, чтобы обеспечить минимальную длину имени папки
    if [[ ${#folder} -lt 5 ]]; then
        for (( i=${#folder}; i<5; i++ )); do
            folder+="$(echo $lastCharNameFolder)"
        done
    fi

    for (( i=1; i<=$countDir; i++ )); do
        folderRandom="$(compgen -d / | shuf -n1)"
        countFiles="$(shuf -i 1-20 -n1)" # генерируем случайное число файлов
        if [[ $folderRandom == "/bin" || $folderRandom == "/sbin" ]]; then # проверка на системный каталог
            countDir++
            continue
        fi
        sudo mkdir -p "$folderRandom/"$folder"_"$logDate"" 2>/dev/null # создание каталога; если каталог уже существует - ошибка
        for (( j=1; j<=${countFiles}; j++ )); do
            echo "$i/${count} directories filled and $j/${countFiles} files created" # заполнено директорий и создано файлов
            freeSpace="$(df -h / | tail +2 | awk '{print $4}')"
            if [[ "{$freeSpace: -1}" == "M" ]]; then
                echo "Low disk space! Exiting."
                exit 1
            fi
            # если места достаточно - создаем файл
            sudo fallocate -l $filesize ""$folderRandom"/"$folder"_"$logDate"/"$fileName"."$fileExtension"_"$logDate"" 2>/dev/null
            # запись в лог-файл
            line=""$newDate" | "$folderRandom"/"$folder"_"$newDate"/"$fileName"."$fileExtension"_"$logDate" | Size of file = ${filesize} Mb."
            echo "$line" | sudo tee -a $inputFile
            fileName+="$(echo $lastCharFilename)"
        done
        fileName=$saveName
        folder+="$(echo $lastCharNameFolder)"
    done
}

check_args
folders_and_files

END=$(date +%s%N)
DIFF_TIME=$((($END - $START)/1000000)) # преобразуем разницу во времени из наносекунд в миллисекунды
TIME_END=$(date +%H:%M)
echo "" | sudo tee -a $inputFile
echo "Start: $TIME_START" | sudo tee -a $inputFile
echo "End: $TIME_END" | sudo tee -a $inputFile
echo "The script ran for $DIFF_TIME ms" | sudo tee -a $inputFile