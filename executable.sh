# Write a shell script that will take a filename as input and check if it is executable. 2. Modify the
# script in the previous question, to remove the execute permissions, if the file is executable


#!/bin/bash

# Check if the user has provided a filename as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Store the filename provided by the user
filename="$1"

# Check if the file exists
if [ ! -e "$filename" ]; then
    echo "File '$filename' does not exist."
    exit 1
fi

# Check if the file is executable
if [ -x "$filename" ]; then
    echo "File '$filename' is executable."

    # Remove the execute permissions
    chmod -x "$filename"
    echo "Execute permissions removed from '$filename'."
else
    echo "File '$filename' is not executable."
fi


#here just add the file name after the executable file if executable then remove the permission then check again
