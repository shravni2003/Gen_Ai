#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int sockfd;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in servaddr;

	// Create UDP socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    	perror("socket creation failed");
    	exit(EXIT_FAILURE);
	}

	// Initialize server address structure
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;
	len = sizeof(servaddr); // len is value/result

	// Send message to server
	const char *message = "Hello from client";
	sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, len);
	printf("Message sent to server\n");

	// Receive message from server
	n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);

	// Close the socket
	close(sockfd);
	return 0;
}
