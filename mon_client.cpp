#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "utils/serialib.h"

#define PORT 5000
#define MAXLINE 1024

using namespace std;

int main()
{
	int client;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;
	int err;

	// ===================== SOCKET INIT =====================

	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0) 
	{
		printf("socket creation failed");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;	// AF_INET: address domain of the socket
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	err = connect(client, (struct sockaddr*)&servaddr,sizeof(servaddr));
	if (err < 0) 
	{
		printf("error : connection failed \n");
	}
    printf("Connection established \n");


	// ===================== CONNECTION OK =====================

	//recv(client,buffer,sizeof(buffer),0);
	//printf("message received : %s \n",buffer);

	while(1){
		// ===================== RECEIVE STREAM =====================
		err =recv(client,buffer,sizeof(buffer),0);
		printf("%s ",buffer);
		if(err<0){
		    printf("error : client message failed \n");
			sleep(1);
		}
		// ===================== TCHAT =====================
		// printf(">>");
		// scanf("%s", &buffer);
		// send(client,buffer,sizeof(buffer),0);

		// err =recv(client,buffer,sizeof(buffer),0);
		// printf("message received : %s \n",buffer);
        // if(err<0){
        //     printf("error : client message failed \n");
        // }else{
        //     printf(">>");
        //     scanf("%s", &buffer);
        //     send(client, buffer, sizeof(buffer), 0);
        // } 
    }
	printf("connection closed");
	close(client);
	return 0;
}
