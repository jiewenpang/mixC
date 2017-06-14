#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 32
int main(int argc, char *argv[]) {
	int sock;
	struct sockaddr_in echoserver;
	char buffer[BUFFSIZE];
	unsigned int echolen;
	int received = 0;

	if (argc != 4) {
		fprintf(stderr, "USAGE: TCPecho <server_ip> <word> <port>\n");
		exit(1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Failed to create socket");
		exit(1);
	}

	memset(&echoserver, 0, sizeof(echoserver));
	echoserver.sin_family = AF_INET;
	echoserver.sin_addr.s_addr = inet_addr(argv[1]);
	echoserver.sin_port = htons(atoi(argv[3]));

	if (connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
		perror("Failed to connect with server");
		exit(1);
	}

	echolen = strlen(argv[2]);
	if (send(sock, argv[2], echolen, 0) != echolen) {
		perror("Mismatch in number of sent bytes");
		exit(1);
	}

	fprintf(stdout, "Received: ");
	while (received < echolen) {
		int bytes = 0;
		if ((bytes = recv(sock, buffer, BUFFSIZE-1, 0)) < 1) {
			perror("Failed to receive bytes from server");
			exit(1);
		}
		received += bytes;
		buffer[bytes] = '\0';
		fprintf(stdout, buffer);
	}

	fprintf(stdout, "\n");
	close(sock);
	exit(0);
}
