#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

int main() {
	int fds[20];
	int opt = 1;
	int client_num = 1;
	struct sockaddr_in conns[20];
	struct pollfd afd[20];
	char data[1024];
	char *msg = "test";
	
	fds[0] = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fds[0], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	ioctl(fds[0], FIONBIO, &opt);

	conns[0].sin_family = AF_INET;
	conns[0].sin_port = htons(5678);
	conns[0].sin_addr.s_addr = htonl(INADDR_ANY);

	bind(fds[0], (struct sockaddr *) &conns[0], sizeof(conns[0]));
	listen(fds[0], 20);
	
	memset(&afd, 0, sizeof(afd));
	afd[0].fd = fds[0];
	afd[0].events = POLLIN;
	while (1) {
		poll(afd, 20, -1);
		int client;
		for(int i = 0; i < client_num; i++) {
			if((afd[i].revents&POLLIN) == POLLIN) {
			 	if (afd[i].revents&POLLIN) {
					client = accept(fds[0], (struct sockaddr *) &conns[i], sizeof(conns[i]));
					send(client, msg, sizeof(msg), 0);
					client_num++;
				/*
				} else {
					send(afd[i].fd, msg, sizeof(msg), 0);	
				*/
				}
			}	
		}

	}	

}
