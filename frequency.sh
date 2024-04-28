# Generate frequency list of all the commands you have used, and show the top 5
# commands along with their count. (Hint: history command hist will give you a list of
# all commands used.

# Get the list of all commands from history and count their frequencies
command_freq=$(history | awk '{print $2}' | sort | uniq -c | sort -nr)

# Display the top 5 commands along with their counts
echo "Top 5 commands:"
echo "$command_freq" | head -n 5
