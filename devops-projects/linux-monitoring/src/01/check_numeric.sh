#!/bin/bash

# Проверка, является ли аргумент числом
if [[ $1 =~ ^[0-9]+$ ]]; then
    echo "Error: Invalid number input."
    exit 1
fi