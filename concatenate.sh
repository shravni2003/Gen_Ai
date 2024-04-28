#!/bin/bash

# Check if the number of arguments is less than 2
if [ $# -lt 2 ]; then
    echo "Error: At least two filenames are required."
    exit 1
fi

# Check if all files exist
for file in "$@"; do
    if [ ! -e "$file" ]; then
        echo "Error: File '$file' does not exist."
        exit 1
    fi
done

# Concatenate the files
cat "$@" > concatenated_file.txt
echo "Files concatenated successfully. Output saved to 'concatenated_file.txt'."



# Write a bash script that takes 2 or more arguments,
# i)All arguments are filenames
# ii)If fewer than two arguments are given, print an error message
# iii)If the files do not exist, print error message
# iv)Otherwise concatenate files