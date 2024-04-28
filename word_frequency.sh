#  Generate a word frequency list for wonderland.txt. Hint: use grep, tr, sort, uniq (or anything else
# that you want


# Use grep to extract words from wonderland.txt, convert them to lowercase,
# and remove punctuation characters
grep -oE '\b[[:alpha:]]+\b' stat.c | tr '[:upper:]' '[:lower:]' | tr -d '[:punct:]' |
# Sort the words alphabetically
sort |
# Use uniq to count the frequency of each word
uniq -c |
# Sort the word frequencies in descending order
sort -nr

