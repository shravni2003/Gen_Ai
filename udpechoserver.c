// 4. Implement echo server using UDP in iterative/concurrent logic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9999
#define BUFFER_SIZE 4096

int main() {
    struct sockaddr_in server_addr, client_addr;
    int sockfd, client_len, recv_len;
    char buffer[BUFFER_SIZE];

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

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while (1) {
        printf("\nWaiting to receive message...\n");

        // Receive message from client
        client_len = sizeof(client_addr);
        if ((recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len)) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        printf("Received %d bytes from %s:%d\n", recv_len, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("Data received: %s\n", buffer);

        // Echo back the received data
        if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr*)&client_addr, client_len) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}


//first run server then client