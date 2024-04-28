#!/bin/bash

# Function to print "Hello World" with given attributes
print_hello_world() {
    echo -e "\e[$1mHello World\e[0m" # Print "Hello World" with the specified attributes
}

# Main script logic
echo "Hello World in Bold:"
print_hello_world "1"

echo "Hello World in Blink:"
print_hello_world "5"

echo "Hello World in Red:"
print_hello_world "31"

echo "Hello World in Green:"
print_hello_world "32"

echo "Hello World in Yellow:"
print_hello_world "33"

echo "Hello World in Blue:"
print_hello_world "34"

echo "Hello World in Magenta:"
print_hello_world "35"

echo "Hello World in Cyan:"
print_hello_world "36"
