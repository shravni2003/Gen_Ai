#!/bin/bash

# Function to check if file exists in folder
check_file_in_folder() {
    local folder="$1"
    local file="$2"

    if [ -e "$folder/$file" ]; then
        echo "File '$file' exists in folder '$folder'"
    else
        echo "File '$file' does not exist in folder '$folder'"
    fi
}

# Function to check if file exists on entire drive
check_file_on_drive() {
    local drive="$1"
    local file="$2"

    if [ -e "$drive/$file" ]; then
        echo "File '$file' exists on drive '$drive'"
    else
        echo "File '$file' does not exist on drive '$drive'"
    fi
}

# Main script logic
if [ $# -ne 2 ]; then
    echo "Usage: $0 <folder> <file>"
    echo "Usage: $0 <drive> <file>"
    exit 1
fi

if [ -d "$1" ]; then
    check_file_in_folder "$1" "$2"
else
    check_file_on_drive "$1" "$2"
fi


here run the code with chmod +x filename then ./filename path to the folder file name