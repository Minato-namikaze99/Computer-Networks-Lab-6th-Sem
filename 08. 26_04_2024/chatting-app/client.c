#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
	int my_sock;
	socklen_t sock_addr_len;

	struct sockaddr_in sock_addr;

	char ch[100];
	
	my_sock = socket(AF_INET, SOCK_STREAM, 0);

	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock_addr.sin_port = htons(44332);
	sock_addr_len = sizeof(sock_addr);
	if(connect(my_sock, (struct sockaddr *)&sock_addr, sock_addr_len) == -1)
	{
		perror("Client failure");
		exit(EXIT_FAILURE);
	}

	scanf(" %99[^\n]", ch);
	write(my_sock, ch, 100);
	while(1){
		//listen(my_sock, 1);
		read(my_sock, &ch, 100);
		printf("server: %s\n", ch);
		scanf(" %99[^\n]", ch);
		write(my_sock, ch, 100);
	}
	close(my_sock);
	return 0;
}
