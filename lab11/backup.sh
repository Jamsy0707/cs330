#!/usr/bin/bash
#file: conditions.sh

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 dirName"
elif [ -d "$1" ]; then
    echo "Directory $1 already exists."
else
    mkdir "$1"
    cp -R *.c $1/
    cp -R *.h $1/

fi