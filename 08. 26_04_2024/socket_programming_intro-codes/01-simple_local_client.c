#include <stdio.h>	// printf(), perror()
#include <stdlib.h>	// exit()
#include <string.h>	// strcpy()
#include <unistd.h>	// read(), write(), close()
#include <sys/un.h>	// struct sockaddr_un
#include <sys/socket.h>	// connect()

int main()
{
	int my_socket;
	socklen_t socket_addr_len;

	struct sockaddr_un socket_address;

	int retval;
	char ch = 'A';

	// creat a socket for the client
	my_socket = socket(AF_UNIX, SOCK_STREAM, 0);

	// name the socket, as given in the server
	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, "my_unix_domain_socket");
	socket_addr_len = sizeof(socket_address);

	// connect to the server socket
	retval = connect(my_socket, (struct sockaddr *)&socket_address, socket_addr_len);
	// check for error
	if( retval == -1 )
	{
		perror("Client Error");
		exit(EXIT_FAILURE);
	}

	// if connected to the server without any error, we can read and write on the socket
	write(my_socket, &ch, 1);
	read(my_socket, &ch, 1);

	printf("Received from Server: %c\n", ch);

	// close connection
	close(my_socket);

	// all done
	return 0;
}

