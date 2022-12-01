#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <string.h>


int main(){
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if (sock_fd == -1){
		perror("error create socket\n");
		return -1;
	}
	printf("socket create success\n");
	int enabled = 1;
	int rez = setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&enabled,sizeof(enabled));
	if(rez<0){
		perror("error setting socket options\n");
		return -1;
	}
	printf("socket options for broadcast enabled successfully\n");
	uint16_t port = 1345; 
	char bc_ip[20] = "172.30.255.255"; 
	struct sockaddr_in bc_addr;
	bc_addr.sin_family = AF_INET;
	bc_addr.sin_port = htons(port);
	inet_aton(bc_ip,&bc_addr.sin_addr);
	socklen_t bc_addr_size = sizeof(bc_addr);
	char buffer[1024] = "of mesaj\0";
	char response[1024];
	struct sockaddr_in receiver_addr;
	socklen_t receiver_addr_size;
	while(1){
		sendto(sock_fd,buffer,strlen(buffer)+1,0,(const struct sockaddr*)&bc_addr,bc_addr_size);
		recvfrom(sock_fd,response,1024,0,(struct sockaddr*)&receiver_addr,&receiver_addr_size);
		printf("%s:%s\n",inet_ntoa(receiver_addr.sin_addr),response);
	}
	return 0;
}
