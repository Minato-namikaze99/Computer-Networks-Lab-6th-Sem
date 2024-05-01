#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int serv_sock, client_sock;
	socklen_t serv_addr_len, client_addr_len;

	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(44332);

	serv_addr_len = sizeof(server_address);

	if(bind(serv_sock, (struct sockaddr *)&server_address, serv_addr_len) == -1)
	{
		perror("Bind error");
		exit(EXIT_FAILURE);
	}

	listen(serv_sock, 1);

	char ch[100];
	printf("Server waiting...\n");

	client_addr_len = sizeof(client_address);

	client_sock = accept(serv_sock, (struct sockaddr *)&client_address, &client_addr_len);
	
	read(client_sock, ch, 100);
	while(1){
		printf("client: %s\nreply: ", ch);
		scanf(" %99[^\n]", ch);
		write(client_sock, ch, 100);
		//listen(serv_sock, 1);
		read(client_sock, ch, 100);
	}
	close(client_sock);

	close(serv_sock);

	return 0;
}
