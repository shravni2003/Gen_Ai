#!/bin/bash

# Function to perform addition
add() {
    echo "Result: $(($1 + $2))"
}

# Function to perform subtraction
subtract() {
    echo "Result: $(($1 - $2))"
}

# Function to perform multiplication
multiply() {
    echo "Result: $(($1 * $2))"
}

# Function to perform division
divide() {
    if [ $2 -eq 0 ]; then
        echo "Error: Division by zero"
    else
        echo "Result: $(($1 / $2))"
    fi
}

# Main script logic
if [ $# -ne 3 ]; then
    echo "Usage: $0 <operand1> <operator> <operand2>"
    exit 1
fi

operand1=$1
operator=$2
operand2=$3

case $operator in
    +)
        add $operand1 $operand2
        ;;
    -)
        subtract $operand1 $operand2
        ;;
    *)
        echo "Error: Invalid operator"
        ;;
esac





//comment chmod +x calculator.sh to runt this code 
//./calculator.sh 10 + 5

