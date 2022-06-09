#include "utils/serialib.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    serialib serial;
    char buff[1024];
    int err;

    //int serial_port = open("/dev/ttyUSB0", O_RDWR);

    printf("launch progRA \n");
    if (serial.openDevice("/dev/ttyACM0", 115200)!=1){
        printf("error \n");
        return 1;
    }
    printf("connection established");
    while(1){
        serial.readChar(buff,10000);
        printf("%s",buff);
    }
    

    serial.closeDevice();
    return 0;
}