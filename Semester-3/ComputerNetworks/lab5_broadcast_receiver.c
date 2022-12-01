#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>

int main(){
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1){
		perror("Error while creating socket.\n");
		return -1;
	}
	printf("Socket created successfully.\n");
	int enabled = 1;
	int rez = setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&enabled,sizeof(enabled));
        if(rez<0){
                perror("error setting socket options\n");
                return -1;
        }
        printf("socket options for broadcast enabled successfully\n");
        uint16_t port = 1345;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t server_size = sizeof(server);
	rez = bind(sock_fd, (const struct sockaddr*)&server, server_size);
	if (rez == -1){
		perror("Bind error.\n");
		return -1;
	}
	printf("Bind executed successfully.\n");
	char buffer[1024];
	char message[] = "ce vreau eu\0";
	struct sockaddr_in sender_addr;
	socklen_t sender_addr_size;
	while(1){
		recvfrom(sock_fd,buffer,512,0,(struct sockaddr*)&sender_addr,&sender_addr_size);
		printf("%s:%s\n",inet_ntoa(sender_addr.sin_addr),buffer);
		sendto(sock_fd, message, strlen(message)+1,0,(const struct sockaddr*)&sender_addr,sender_addr_size);
	}
}


