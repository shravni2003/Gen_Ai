# Write a shell script to download a given file from ftp://10.10.13.16 if it exists on ftp.
# (use lftp, get and mget commands)

#!/bin/bash

# Use lftp to connect to the FTP server and list the files
lftp -c "open ftp://10.10.13.16; ls"

# Check if the listing was successful
if [ $? -eq 0 ]; then
    echo "File listing successful."
else
    echo "Failed to list files on the FTP server."
fi
