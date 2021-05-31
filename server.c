#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

int main() {
	int serv;
	int opt = 1;
	struct sockaddr_in serv_st;
	struct pollfd afd[20];
	char data[1024];
	
	serv = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	ioctl(serv, FIONBIO, &opt);

	serv_st.sin_family = AF_INET;
	serv_st.sin_port = htons(5678);
	serv_st.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(serv, (struct sockaddr *) &serv_st, sizeof(serv_st));
	listen(serv, 20);
	
	afd[0].fd = serv;
	afd[0].events = POLL_IN;
	do {
		poll(afd, 1, 3 * 60 * 1000);
		

	}	

}
