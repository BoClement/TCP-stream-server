#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils/serialib.h"
#include "socket.h"

using namespace std;

/*  
	struct sockaddr_in
	{
		short   sin_family;
		u_short sin_port;
		struct  in_addr sin_addr;
		char    sin_zero[8];
	};
*/
int main()
{
    int client, server;
    bool isExit = false;
    char buffer[MAXLINE];
	int err;
    struct sockaddr_in server_addr;
    socklen_t size;
    serialib serial;

    // ===================== INIT SOCKET =====================

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) 
    {
        printf("Error establishing socket \n");
        exit(1);
    }
	printf("Socket server has been created \n");


	server_addr.sin_family = AF_INET;	// AF_INET: address domain of the socket
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);	// INADDR_ANY : IP address of the host
    server_addr.sin_port = htons(PORT); // convert port
    
	err = bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr));
	// binds a socket to an address : addr of host and port number 

	if (err < 0) 
    {
        printf("error : binding failed\n");
        return -1;
    }
    // ===================== INIT STREAM =====================

    if (serial.openDevice("/dev/ttyACM0", 115200)!=1){
        printf("error : connection to the port failed \n");
        return 1;
    }
    printf("serial port connectedd \n");

    // ===================== CONNECTION STREAM OK =====================
    printf("wait for clients ...\n");

    listen(client, 5);	// block the programme while no client

    int clientCount = 1;

    server = accept(client,(struct sockaddr *)&server_addr,&size);

    if (server < 0) 
        printf("error : client not accept \n");
    printf("Connection established \n");

	// ===================== CONNECTION SOCKET OK =====================
    


    //strcpy(buffer, "=> Server connected...\n");
    //send(server, buffer, sizeof(buffer), 0);

    while (server > 0) 
    { 
        // ===================== START STREAM =====================

        err=serial.readChar(buffer,1000);
        send(server, buffer, sizeof(buffer), 0);
        printf("%s",buffer);
        if(err<0){
            printf("error : client message failed \n");
            sleep(1);
        }
	    

	    // ===================== TCHAT =====================
        // err = recv(server, buffer, sizeof(buffer), 0);
        // printf("message received : %s \n",buffer);
        // if(err<0){
        //     printf("error : client message failed \n");
        // }else{
        //     printf(">>");
        //     scanf("%s", &buffer);
        //     send(server, buffer, sizeof(buffer), 0);
        // } 
    }
	
	// ===================== END =====================
	printf("connection closed");
    serial.closeDevice();
    close(server);
    close(client);
    return 0;
}