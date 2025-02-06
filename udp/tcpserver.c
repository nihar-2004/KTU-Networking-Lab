#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
	int server, newSock;
	char buffer[1024];
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t addrSize;
	
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(6265);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(server,(struct sockaddr *) &servAddr, sizeof(servAddr));
	if (listen(server,5)==0)
		printf("Listening\n");
	else
		printf("Error\n");
		
	newSock = accept(server,(struct sockaddr *) &store, &addrSize);
	recv(newSock, buffer, 1024,0);
	printf("2.Data received: %s",buffer);
	strcpy(buffer,"Hi this is server\n");
	printf("3. Sending data to client\n");
	send(newSock,buffer,19,0);
	close(newSock);
	close(server);


}
