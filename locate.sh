#!/bin/bash

# Check if the user has provided a file name as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Store the file name provided by the user
filename="$1"

# Use the find command to search for the file in the system
echo "Searching for '$filename' in the system..."

# Perform the search using find
results=$(find / -name "$filename" 2>/dev/null)

# Check if any results were found
if [ -n "$results" ]; then
    echo "Found the following occurrences:"
    echo "$results"
else
    echo "File '$filename' not found in the system."
fi


Write a shell script to find the given file in the system using find or locate command