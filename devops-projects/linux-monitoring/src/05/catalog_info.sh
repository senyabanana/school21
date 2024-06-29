#!/bin/bash

START_TIME=$(date +"%s.%N")
COUNT_FOLDERS="$(ls -l $param | grep -c ^d)"
TOP_FOLDERS=""
out=$(sudo du -h "$1" | sort -rh | head -5 | awk '{print" - "$2", "$1}')
IFS=$'\n'
i=0
for var in $out
do
    ((i +=1))
TOP_FOLDERS+="\n$i $var"
done
COUNT_FILES="$(sudo find "$param" -type f|wc -l)"
COUNT_CONF_FILES="$(sudo find "$param" -name "*.conf" | wc -l)"
COUNT_TXT_FILES="$(sudo find "$param" -name "*.txt" | wc -l)"
COUNT_EXE_FILES="$(sudo find "$param" -type f -executable | wc -l)"
COUNT_LOG_FILES="$(sudo find "$param" -name "*.log" | wc -l)"
COUNT_ZIP_FILES="$(sudo find $param -name "*.zip" -o -name "*.7z" -o -name "*.rar" -o -name "*.tar" | wc -l)"
COUNT_SYM_LINKS="$(sudo find "$param" -type l | wc -l)"
TOP_FILES=""
out="$(sudo find "$param" -type f -not -path '*/\.*' -exec du -h {} + 2>/dev/null | sort -hr | head -n 10 )"
IFS=$'\n'
i=0
for var in $out
do
    ((i += 1))
    file=$(echo "$var" | awk '{print $2}')
    size=$(echo "$var" | awk '{print $1}' | sed -e 's:K: Kb:g' | sed 's:M: Mb:g' | sed 's:G: Gb:g' )
    type=$(echo "$var" | awk '{ tp=split($2,type,".") ; print type[tp] }' )
    TOP_FILES+="\n$i - $file, $size, $type"
done
TOP_EXE_FILES=""
out="$(sudo find "$param" -type f -executable -not -path '*/\.*' -exec du -h {} +  2>/dev/null | sort -hr | head -n 10 )"
IFS=$'\n'
i=0
for var in $out
do
    ((i += 1))
    path=$(echo "$var" | awk '{print $2}')
    size=$(echo "$var" | awk '{print $1}' | sed -e 's:K: Kb:g' | sed 's:M: Mb:g' | sed 's:G: Gb:g' )
    md5=$(md5sum "$path"|  awk '{print $1}')
    TOP_EXE_FILES+="\n$i - $path, $size, $md5"
done
END_TIME=$(date +%s%N)
TIME=$(bc <<< "$START_TIME - $END_TIME")