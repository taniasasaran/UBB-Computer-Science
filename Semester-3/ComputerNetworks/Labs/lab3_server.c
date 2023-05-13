#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

int serve_client(int client_fd){
	uint32_t nr;
	int rez = read(client_fd, &nr, sizeof(uint32_t));
	if(rez == -1){
		perror("read error.\n");
		close(client_fd);
		return -1;
	}
	nr = ntohl(nr);
	printf("client said: %d\n", nr);
	char buffer[nr+1];
	for(int i=0; i<nr+1; i++)
		buffer[i] = '\0';
	buffer[nr] = '\0';
	rez = read(client_fd, buffer, nr);
	if(rez==-1){
		perror("read error.\n");
		close(client_fd);
		return -1;
	}
	printf("client said: %s\n", buffer);
	return 0;
}

int main(){
	uint16_t port = 1234;
	char address[256] = "172.30.117.34";
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1){
		perror("Socket error!\n");
		return -1;
	}
	printf("Socket created successfully!\n");
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_aton(address,&server_addr.sin_addr);
	socklen_t server_addr_len = sizeof(server_addr);
	int rez = bind(socket_fd,(const struct sockaddr*)&server_addr,server_addr_len);
	if(rez == -1){
		perror("Bind error.\n");
		return -1;
	}
	printf("Successfully bound to address %s and port %d.\n", address, port);
	int backlog = 7;
	rez = listen(socket_fd,backlog);
	if(rez == -1){
		perror("Listening error.\n");
		return -1;
	}
	printf("Successfully established a listening queue with %d places.\n", backlog);
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while(1){
		int client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_len);
		if(client_fd == -1){
			perror("Accept error.\n");
			continue;
		}
		printf("Client with IP %s and port %d has connected.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		if(fork() == 0){
			serve_client(client_fd);
		}
	}
	return 0;
}
