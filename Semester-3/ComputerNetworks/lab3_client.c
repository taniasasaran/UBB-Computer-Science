#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

int main(){
	uint16_t port = 1234;
	char server_address[256] = "172.30.117.34";
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1){
		perror("error creating socket!\n");
		return -1;
	}
	printf("Successfully created socket!\n");
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	inet_aton(server_address, &client_addr.sin_addr);
	socklen_t client_addr_len = sizeof(client_addr);
	int res = connect(socket_fd, (const struct sockaddr*)&client_addr, client_addr_len);
	if(res == -1){
		perror("connect error!\n");
		return -1;
	}
	printf("successfully connected to address %s and port %d.\n",server_address, port);
	char mesaj[100] = "brrp\0";
	int len_mesaj = strlen(mesaj);
	printf("%d\n", len_mesaj);
	len_mesaj = htonl(len_mesaj+1);
	write(socket_fd,&len_mesaj,sizeof(int));
	write(socket_fd,mesaj,strlen(mesaj)+1);
	return 0;
}
