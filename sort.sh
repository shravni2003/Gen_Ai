#!/bin/bash

# Function to sort numbers in ascending order
sort_numbers() {
    sorted=$(echo "$@" | tr ' ' '\n' | sort -n) # Convert space-separated numbers to newline-separated, sort numerically
    echo "Sorted numbers in ascending order: $sorted"
}

# Main script logic
if [ $# -ne 10 ]; then
    echo "Usage: $0 <num1> <num2> ... <num10>"
    exit 1
fi

sort_numbers "$@"
