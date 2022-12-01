#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>

int main(){
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1){
		perror("Error while creating socket.\n");
		return -1;
	}
	printf("Socket created successfully.\n");
	uint16_t port = 1234;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t server_size = sizeof(server);
	int rez = bind(sock_fd, (const struct sockaddr*)&server, server_size);
	if (rez == -1){
		perror("Bind error.\n");
		return -1;
	}
	printf("Bind executed successfully.\n");
	char buffer[1024];
	struct sockaddr_in sender_addr;
	socklen_t sender_addr_size;
	while(1){
		recvfrom(sock_fd,buffer,512,0,(struct sockaddr*)&sender_addr,&sender_addr_size);
		printf("%s:%s\n",inet_ntoa(sender_addr.sin_addr),buffer);
	}
}


