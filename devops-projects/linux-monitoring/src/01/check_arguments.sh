#!/bin/bash

# Проверка на наличие одного аргумента
if [ $# -ne 1 ]; then
    echo "Error: script must be run with one argument."
    exit 1
fi