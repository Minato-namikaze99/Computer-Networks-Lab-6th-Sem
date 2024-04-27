#include <stdio.h>	// printf(), perror()
#include <sys/socket.h>	// socket(), bind(), listen(), accept()
#include <netinet/in.h>	// struct sockaddr_in
#include <arpa/inet.h>	// inet_addr(), htons()
#include <unistd.h>	// read(), write(), close()
#include <stdlib.h>	// exit()

int main()
{
	int server_socket, client_socket;
	socklen_t server_addr_len, client_addr_len;

	struct sockaddr_in server_address;	// check 'netinet/in.h' for the struct
	struct sockaddr_in client_address;

	int retval;

	// create the socket resource or file handle
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	// int socket(int domain, int type, int protocol);
	// domain  : AF_UNIX, AF_INET, AF_INET6 etc.
	// type    : SOCK_STREAM, SOCK_DGRAM etc.
	// protocol: 0 (see the man page)

	// name the socket (assign address)
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	// or bind on any available n/w interface:
	// server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(44332);	// endian-ness conversion, ie. byte ordering
	server_addr_len = sizeof(server_address);
	retval = bind(server_socket, (struct sockaddr *)&server_address, server_addr_len);
	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if( retval == -1 )
	{
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}
	
	// create a connection queue, and wait for clients
	// on error 'listen' returns -1.  should check this in a real-world program
	listen(server_socket, 5);
	// int listen(int sockfd, int backlog);
	
	// accept incoming connection
	for(int i=0; i<5; i++)
	{
		char ch;
		printf("Server waiting...\n");

		client_addr_len = sizeof(client_address);
		client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
		// int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
		// 'accept' can also return -1 on error.  should check this in a real-world program

		// read and write on the client_socket
		read(client_socket, &ch, 1);
		ch++;
		write(client_socket, &ch, 1);

		// close the client_socket
		close(client_socket);
	}

   // close the server socket
   close(server_socket);

   // all done
   return 0;
}

