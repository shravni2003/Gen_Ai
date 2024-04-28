#!/bin/bash

# Function to display disk partitions and their sizes
show_disk_partitions() {
    echo "Disk partitions and their sizes:"
    df -h
}

# Function to display disk usage (free space)
show_disk_usage() {
    echo "Disk usage (free space):"
    du -h --max-depth=1 /
}

# Main script logic
show_disk_partitions
echo ""
show_disk_usage
