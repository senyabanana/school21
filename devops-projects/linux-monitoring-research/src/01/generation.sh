#!/bin/bash

inputFile="logfile.txt"
sudo touch $inputFile

function check_args {
    firstChar=$(echo $param1 | head -c 1)
    if [[ "$firstChar" != "/" ]]; then
        # путь введен некорректно
        echo "Error {$param1}: path entered incorrectly!"
        exit 1
    fi

    if [[ $param2 =~ [^0-9] ]]; then
        # колличество вложенных папок некорректно
        echo "Error {$param2}: the number of subfolders is incorrect!"
        exit 1
    fi

    export countChar=${#param3}
    if [[ ($countChar -gt 7) ]]; then
        # в названии папок должно быть не более 7 знаков
        echo "Error {$param3}: folder names must contain mo more than 7 characters!"
        exit 1
    fi

    if [[ $param3 =~ [^A-Za-z] ]]; then
        # используется только английский алфавит
        echo "Error {$param3}: only letters of the English alphabet!"
        exit 1
    fi

    if [[ $param4 =~ [^0-9] ]]; then
        # колличество файлов в каждой папке некорректно
        echo "Error {$param4}: the number of files in each folder is incorrect!"
        exit 1
    fi

    if [[ $param4 -gt 100 ]]; then
        # папки засорены файлами
        echo "Error {$param4}: too many files. The number should not exceed 100!"
        exit 1
    fi

    if [[ ! "$param5" =~ ^([A-Za-z]{1,7}).([A-Za-z]{1,3})$ ]]; then
        # для имени файла - не более 7 знаков, для расширения - не более 3 знаков
        echo "Error {$param5}: for the file name - no more than 7 characters, for the extension - no more than 3 characters!"
        exit 1
    fi

    filesize=$param6
    onlysize=${filesize%kb}
    
    if [[ ! "$param6" =~ ^([0-9]+kb)$ ]]; then
        # формат размера файла введен некорректно
        echo "Error ${param6}: the file size format is entered incorrectly!"
        exit 1
    fi

    if [[ ! $onlysize > 0 || ! $onlysize -le 100 ]]; then
        # размер файлов должен быть не более 100кб
        echo "Error {$param6}: file size should be no more than 100kb!"
        exit 1
    fi
}

function folders_and_files {
    folder=$param3 # имя начальной папки
    filename=$(echo $param5 | awk -F. '{print $1}') # имя файла
    fileExtension=$(echo $param5 | awk -F. '{print $2}') # расширение файла
    lastCharNameFolder=${param3: -1} # последний символ из имени начальной папки
    fileName=$filename # имя файла, которое будет изменяться для каждого нового файла
    saveName=$fileName # сохраняет исходное имя файла
    lastCharFileName=${fileName: -1} # последний символ из имени файла
    logDate="$(date +"%d%m%y")" # текущая дата для созданных файлов и папок
    newDate="DATE = $(date +"%d.%m.%y")" # форматированная строка с текущей датой для записи в лог

    # если имя начальной папки имеет длину менее 4 символов, то к нему добавляются символы из переменной
    # до достижения длины в 4 символа, чтобы обеспечить минимальную длину имени папки
    if [[ ${#folder} -lt 4 ]]; then
        for (( i=${#folder}; i<4; i++ )); do
            folder+="$(echo $lastCharNameFolder)"
        done
    fi

    for (( i=1; i <$param2; i++ )); do
        sudo mkdir -p "$param1/"$folder"_"$logDate""
        for (( j=1; j<=$param4; j++ )); do
            freeSpace=$(df / | tail +2 | awk '{print $4}')
            if [[ "$freeSpace" -lt 1048576 ]]; then
                echo "Low disk space! Exiting."
                exit 1
            fi
            # если места достаточно - создаем файл
            sudo fallocate -l $filesize ""$param1"/"$folder"_"$logDate"/"$fileName"."$fileExtension"_"$logDate""
            # запись в лог-файл
            line=""$newDate" | "$param3"/"$folder"_"$logDate"/"$fileName"."$fileExtension"_"$logDate" | Size of file = ${filesize}."
            echo "$line" | sudo tee -a $inputFile
            # чтобы следующий файл имел отличающее название
            fileName+="$(echo $lastCharFilename)"
        done
        fileName=$saveName
        folder+="$(echo $lastCharNameFolder)"
    done
}

check_args
folders_and_files