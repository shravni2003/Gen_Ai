#!/bin/bash

# Check if the user has provided a URL as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <URL>"
    exit 1
fi

# Store the URL provided by the user
url="$1"

# Use wget to download the webpage
echo "Downloading webpage from '$url'..."

# Perform the download using wget
wget -q -O downloaded_page.html "$url"

# Check if the download was successful
if [ $? -eq 0 ]; then
    echo "Webpage downloaded successfully."
else
    echo "Failed to download webpage from '$url'."
    exit 1
fi


Write a shell script to download webpage at given url using command(wget)
after chmod then run executable with argument of any website.com 
