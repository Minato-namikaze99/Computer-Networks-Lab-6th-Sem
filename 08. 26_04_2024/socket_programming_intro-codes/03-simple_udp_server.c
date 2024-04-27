#include <stdio.h>	// printf(), perror()
#include <sys/socket.h>	// socket(), bind(), recvfrom(), sendto()
#include <netinet/in.h>	// struct sockaddr_in
#include <arpa/inet.h>	// inet_addr(), htons()
#include <unistd.h>	// close()
#include <stdlib.h>	// exit()

int main()
{
	int my_socket;
	socklen_t server_addr_len, client_addr_len;

	struct sockaddr_in server_address;	// check 'netinet/in.h' for the struct
	struct sockaddr_in client_address;

	int retval;

	// create the socket resource or file handle
	my_socket = socket(AF_INET, SOCK_DGRAM, 0);
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
	retval = bind(my_socket, (struct sockaddr *)&server_address, server_addr_len);
	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if( retval == -1 )
	{
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}
	
	// read incoming request and reply to it	
   char ch;
	printf("Server waiting...\n");

	client_addr_len = sizeof(client_address);

   recvfrom(my_socket, &ch, 1, MSG_TRUNC, (struct sockaddr *)&client_address, &client_addr_len);
   // ssize_t recvfrom(int sockfd, void buf[restrict .len], size_t len, int flags, struct sockaddr *_Nullable restrict src_addr, socklen_t *_Nullable restrict addrlen);
   ch++;
   sendto(my_socket, &ch, 1, MSG_CONFIRM, (const struct sockaddr *)&client_address, client_addr_len);
   // ssize_t sendto(int sockfd, const void buf[.len], size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

   // close the socket
   close(my_socket);

   // all done
   return 0;
}
