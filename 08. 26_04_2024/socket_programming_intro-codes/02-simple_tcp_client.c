#include <stdio.h>	// printf(), perror()
#include <stdlib.h>	// exit()
#include <unistd.h>	// read(), write(), close()
#include <netinet/in.h>	// struct sockaddr_in
#include <arpa/inet.h>	// inet_addr(), htons()
#include <sys/socket.h>	// socket(), connect()
#include <unistd.h>

int main()
{
	int my_socket;
	socklen_t socket_addr_len;

	struct sockaddr_in socket_address;

	int retval;
	char ch = 'A';

	// creat a socket for the client
	my_socket = socket(AF_INET, SOCK_STREAM, 0);

	// name the socket, as given in the server
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(44332);
	socket_addr_len = sizeof(socket_address);

	// connect to the server socket
	retval = connect(my_socket, (struct sockaddr *)&socket_address, socket_addr_len);
   // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// check for error
	if( retval == -1 )
	{
		perror("Client Error");
		exit(EXIT_FAILURE);
	}

	sleep(10);

	// if connected to the server without any error, we can read and write on the socket
	write(my_socket, &ch, 1);
	read(my_socket, &ch, 1);

	printf("Received from Server: %c\n", ch);

	// close connection
	close(my_socket);

	// all done
	return 0;
}

