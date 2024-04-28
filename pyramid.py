# #Write a program to display the following pyramid. The number of lines in the
# pyramid should not be hard-coded. It should be obtained from the user. The
# pyramid should appear as close to the center of the screen as possible.
# (Hint: Basics n loops

def display_pyramid(num_lines):
    """
    Display a pyramid with the specified number of lines.
    
    Args:
    - num_lines: The number of lines in the pyramid.
    """
    # Loop through each line
    for i in range(1, num_lines + 1):
        # Print spaces to center the pyramid
        print(" " * (num_lines - i), end="")
        
        # Print stars for the current line
        print("*" * (2 * i - 1))

# Get the number of lines from the user
num_lines = int(input("Enter the number of lines for the pyramid: "))

# Display the pyramid
display_pyramid(num_lines)
