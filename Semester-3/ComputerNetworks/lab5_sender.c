#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1){
		perror("Error creating socket.\n");
		return -1;
	}
	printf("Socket created successfully.\n");
	struct sockaddr_in receiver_addr;
	char receiver_ip[20] = "172.30.117.34";
	uint16_t port = 1234;
	receiver_addr.sin_family = AF_INET;
	receiver_addr.sin_port = htons(port);
	inet_aton(receiver_ip, &receiver_addr.sin_addr);
	socklen_t receiver_addr_size = sizeof(receiver_addr);
	char message[1024] = "buna siua\0";
	while(1){
		sendto(sock_fd,message,strlen(message)+1,0,(const struct sockaddr*)&receiver_addr,receiver_addr_size);
	}
	return 0;
}
