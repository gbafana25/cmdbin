#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/poll.h>
#include <stddef.h>

//#include "database.h"
#include "linkgen.h"


int main() {
	int server, client;
	int opt = 1;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	char short_link[8];
	memset(&short_link, 0, sizeof(short_link));
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == -1) {
		perror("Couldn't create socket");
		exit(0);
	}

	setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5678);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("Couldn't bind socket");
		exit(1);
	}

	if(listen(server, 5) == -1) {
		perror("couldn't start listening");
		exit(1);
	}
	
	socklen_t client_size = sizeof(serv_addr);
	while (1) {
		client = accept(server, (struct sockaddr *) &client_addr, &client_size);
		make_short_link(8, short_link);
		send(client, short_link, strlen(short_link), 0);
		memset(&short_link, 0, sizeof(short_link));

	}	

}

