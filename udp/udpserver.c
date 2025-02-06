#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
	int server;
	char servMsg[2000],cliMsg[2000];
	struct sockaddr_in servAddr, client_addr;
	server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (server<0){
		printf("Error while creating socket\n");
		exit(1);
	}
	printf("Socket created successfully\n");
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(2002);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(server, (struct sockaddr*) &servAddr, sizeof(servAddr))<0){
		printf("Couldn't bind to the port\n");
		exit(1);
	}
	socklen_t client_struct_length = sizeof(client_addr);

	printf("Binding done\n");
	printf("Listening...\n");
	if(recvfrom(server,cliMsg,sizeof(cliMsg),0,(struct sockaddr *)&client_addr, &client_struct_length)<0){
		printf("Couldn't receive\n");
		exit(1);
	}
	printf("Msg from client: %s",cliMsg);
	
	strcpy(servMsg,"Hello from server\n");
	if(sendto(server,servMsg,strlen(servMsg),0,(struct sockaddr*)&client_addr, client_struct_length)<0){
		printf("Couldn't send\n");
		exit(1);
	}
	close(server);
}

