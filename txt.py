# Take any txt file and count word frequencies in a file.(hint : file handling + basics )

def count_word_frequencies(file_name):
    """
    Count word frequencies in a text file.
    
    Args:
    - file_name: The name of the text file to read.
    
    Returns:
    - A dictionary containing word frequencies.
    """
    word_freq = {}
    
    # Open the file in read mode
    with open(file_name, 'r') as file:
        # Read each line from the file
        for line in file:
            # Split the line into words
            words = line.split()
            # Count the frequency of each word
            for word in words:
                word = word.lower()  # Convert to lowercase to treat words case-insensitively
                # Increment the frequency count for the word
                word_freq[word] = word_freq.get(word, 0) + 1
    
    return word_freq

# Example usage:
file_name = input("Enter the name of the text file: ")
word_frequencies = count_word_frequencies(file_name)

# Print the word frequencies
print("Word Frequencies:")
for word, freq in word_frequencies.items():
    print(f"{word}: {freq}")



#run python3 txt.py then filename