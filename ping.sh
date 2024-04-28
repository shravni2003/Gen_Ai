#!/bin/bash

# Function to check network connectivity
check_network() {
    ping -c 1 google.com >/dev/null 2>&1 # Ping Google's server once
    if [ $? -eq 0 ]; then
        echo "Network is UP"
    else
        echo "Network is DOWN"
    fi
}

# Main script logic
check_network


Write a program to check whether system is in network or not using ’ping’ command using shell
script.