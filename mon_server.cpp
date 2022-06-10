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
#include <pthread.h>

using namespace std;

int client[5], server[5];
bool isExit = false;
char buffer[MAXLINE];
int err;
struct sockaddr_in server_addr;
socklen_t size;
serialib serial;
int clientCount = 1;
pthread_t the_thread[5];


// ===================== THREAD CALLBACK ======================

void* server_thread(void* arg) {
    printf("########### \n");
    long id = (long)arg;
    printf("Serial stream redirect to client %d \n", id);
    sleep(0.5);

    while(1)
    {
        err=serial.readBytes(buffer,1000); //conflict to the serial port when more than one client
        send(client[id], buffer, sizeof(buffer), 0);
        if(err<0){
            printf("error : client %d message failed \n",id);
        }
    }
    close(client[id]);
}

// ========================== MAIN ============================
int main()
{
    // -------------- INIT SOCKET --------------

    client[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (client[0] < 0) 
    {
        printf("Error establishing socket \n");
        exit(1);
    }
	printf("Socket server has been created \n");


	server_addr.sin_family = AF_INET;	// AF_INET: address domain of the socket
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);	// INADDR_ANY : IP address of the host
    server_addr.sin_port = htons(PORT); // convert port
    
	err = bind(client[0], (struct sockaddr*)&server_addr,sizeof(server_addr));
	// binds a socket to an address : addr of host and port number 

	if (err < 0) 
    {
        printf("error : binding failed\n");
        return -1;
    }
    // -------------- INIT STREAM --------------

    if (serial.openDevice("/dev/ttyACM0", 115200)!=1){
        printf("error : connection to the port failed \n");
        return 1;
    }
    printf("serial port connectedd \n");

    // -------------- CONNECTION STREAM OK --------------
    printf("wait for clients ...\n");

    listen(client[0], 5);	// block the programme while no client

    
	// -------------- CONNECTION SOCKET OK --------------
    


    //strcpy(buffer, "=> Server connected...\n");
    //send(server, buffer, sizeof(buffer), 0);

    while (1) 
    { 
        // -------------- START STREAM --------------
        client[clientCount] = accept(client[0],(struct sockaddr *)&server_addr,&size);
        if (client[clientCount] < 0) 
            printf("error : client not accept \n");
        printf("Connection established \n");

        pthread_create(&the_thread[clientCount], NULL, server_thread, (void*)clientCount);
        printf("THREAD OK \n");
        //pthread_detach(the_thread[clientCount]);
        clientCount++;

	    // -------------- TCHAT --------------
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
	
	// -------------- END --------------
	printf("connection closed");
    serial.closeDevice();
    return 0;
}