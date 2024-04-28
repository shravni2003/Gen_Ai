// Write a program for chatting between two/three users to demonstrate IPC using
// message passing (msgget, msgsnd, msgrcv )


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

#define MAX_MSG_SIZE 256
#define MSG_KEY 1234

struct message {
	long mtype;
	char mtext[MAX_MSG_SIZE];
};

int main() {
	int msgid;
	struct message msg;
	key_t key;

	// Create a message queue
	key = ftok("/tmp", MSG_KEY);
	if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
    	perror("msgget");
    	exit(1);
	}

	// Fork a child process for receiving messages
	pid_t pid = fork();

	if (pid == -1) {
    	perror("fork");
    	exit(1);
	} else if (pid == 0) { // Child process - Receiving messages
    	while (1) {
        	if (msgrcv(msgid, &msg, MAX_MSG_SIZE, 1, 0) == -1) {
            	perror("msgrcv");
            	exit(1);
        	}
        	printf("User 1: %s\n", msg.mtext);
        	printf("Enter your message (User 2): ");
        	fgets(msg.mtext, MAX_MSG_SIZE, stdin);
        	msg.mtype = 1;
        	// Remove the newline character from the message
        	msg.mtext[strcspn(msg.mtext, "\n")] = 0;
        	// Send the message
        	if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            	perror("msgsnd");
            	exit(1);
        	}
    	}
	} else { // Parent process - Sending messages
    	while (1) {
        	printf("Enter your message (User 1): ");
        	fgets(msg.mtext, MAX_MSG_SIZE, stdin);
        	msg.mtype = 1;
        	// Remove the newline character from the message
        	msg.mtext[strcspn(msg.mtext, "\n")] = 0;
        	// Send the message
        	if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            	perror("msgsnd");
            	exit(1);
        	}
        	if (msgrcv(msgid, &msg, MAX_MSG_SIZE, 1, 0) == -1) {
            	perror("msgrcv");
            	exit(1);
        	}
        	printf("User 2: %s\n", msg.mtext);
    	}
	}

	// Clean up: Remove the message queue
	if (msgctl(msgid, IPC_RMID, NULL) == -1) {
    	perror("msgctl");
    	exit(1);
	}

	return 0;
}

//gcc chatIpc.c -o chat -lrt
//./chat