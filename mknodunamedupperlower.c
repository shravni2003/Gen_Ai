// # 66.write prog using FIFO/mknod (named pipe)/unmanned pipe for uppercase to lowercase conversion

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUT_FIFO "/tmp/input_fifo"
#define OUTPUT_FIFO "/tmp/output_fifo"

int main()
{
    // Create the input FIFO (named pipe) if it doesn't exist
    if (mkfifo(INPUT_FIFO, 0666) == -1)
    {
        fprintf(stderr, "Error creating input FIFO\n");
        exit(EXIT_FAILURE);
    }

    // Create the output FIFO (named pipe) if it doesn't exist
    if (mkfifo(OUTPUT_FIFO, 0666) == -1)
    {
        fprintf(stderr, "Error creating output FIFO\n");
        exit(EXIT_FAILURE);
    }

    // Open the input FIFO for reading
    int inputFd = open(INPUT_FIFO, O_RDONLY);
    if (inputFd == -1)
    {
        fprintf(stderr, "Error opening input FIFO for reading\n");
        exit(EXIT_FAILURE);
    }

    // Open the output FIFO for writing
    int outputFd = open(OUTPUT_FIFO, O_WRONLY);
    if (outputFd == -1)
    {
        fprintf(stderr, "Error opening output FIFO for writing\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    ssize_t bytesRead;

    // Read from the input FIFO and convert to lowercase
    while ((bytesRead = read(inputFd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            buffer[i] = tolower(buffer[i]);
        }

        // Write the converted text to the output FIFO
        if (write(outputFd, buffer, bytesRead) == -1)
        {
            fprintf(stderr, "Error writing to output FIFO\n");
            exit(EXIT_FAILURE);
        }
    }

    // Close the FIFOs
    close(inputFd);
    close(outputFd);

    // Remove the FIFOs
    unlink(INPUT_FIFO);
    unlink(OUTPUT_FIFO);

    printf("Conversion complete.\n");

    return 0;
}
