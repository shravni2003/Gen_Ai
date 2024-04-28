#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9999
#define BUFFER_SIZE 4096

int main() {
    struct sockaddr_in server_addr;
    int sockfd;
    char buffer[BUFFER_SIZE];
    socklen_t server_len;

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    while (1) {
        printf("Enter message to send (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove newline character from the input
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send message to the server
        server_len = sizeof(server_addr);
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, server_len) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        // Receive response from server
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        printf("Received response: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
