#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
	int server, newSock, k=5, m=1, p;
	char buffer[1024];
	struct sockaddr_in servAddr, store;
	socklen_t addrSize = sizeof(servAddr);
	server = socket(PF_INET, SOCK_STREAM, 0);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(5600);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(servAddr.sin_zero,'\0',sizeof(servAddr.sin_zero));
	bind(server,(struct sockaddr*)&servAddr, sizeof(servAddr));
	if (listen(server,5) == 0){
		printf("Listening\n");
	} else {
		printf("Error\n");
		exit(1);
	}
	newSock = accept(server, (struct sockaddr*)&store, &addrSize);
	if (newSock == -1){
		printf("Error in creating socket\n");
		exit(1);
	}
	while(k!=0){
		int y = recv(newSock, buffer, sizeof(buffer),0);
		if (y==-1){
			printf("Error in receiving\n");
			exit(1);
		}
		if (strncmp(buffer,"frame",5)==0){
			printf("Received %d successfully\n",m);
		} else {
			printf("Frame %d not received\n",m);
		}
		if (m%2 ==0){
			strcpy(buffer,"ack");
		} else {
			strcpy(buffer,"kca");
			printf("Ack lost\n");
			for (p=1;p<=3;p++){
				printf("Waiting for %d seconds\n",p);
				sleep(1);
			}
			printf("Retransmitting Ack\n");
			strcpy(buffer, "ack");
		}
		printf("Sending ack\n");
		int z = send(newSock, buffer, strlen(buffer), 0);
		if (z == -1){
			printf("error in sending\n");
			exit(1);
		}
		k--;
		m++;
	}
	close(newSock);
	close(server);
	return(0);
}
