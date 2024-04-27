#include <stdio.h>	// printf(), perror()
#include <stdlib.h>	// exit()
#include <unistd.h>	// close()
#include <netinet/in.h>	// struct sockaddr_in
#include <arpa/inet.h>	// inet_addr(), htons()
#include <sys/socket.h>	// socket(), recvfrom(), sendto()

int main()
{
	int my_socket;
	socklen_t socket_addr_len;

	struct sockaddr_in socket_address;

	char ch = 'A';

	// creat a socket for the client
	my_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// name the socket, as given in the server
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(44332);
	socket_addr_len = sizeof(socket_address);

	// send and receive data to/from the server
   sendto(my_socket, &ch, 1, MSG_CONFIRM, (const struct sockaddr *)&socket_address, socket_addr_len);
   recvfrom(my_socket, &ch, 1, MSG_TRUNC, (struct sockaddr *)&socket_address, &socket_addr_len);

	printf("Received from Server: %c\n", ch);

	// close connection
	close(my_socket);

	// all done
	return 0;
}

