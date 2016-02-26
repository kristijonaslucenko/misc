#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <serial.h>
#include <receiveFrame.h>


char buf[255];
int res;


int main()
{
    char* pbuff;
    char* frame;

    frame = (char*)malloc(255);
    frame[10] = 0;

    int fd = serialInit();

    pbuff = serialRead(fd);

    int size;

    size = getPacket(pbuff, frame);

    printf("Size: %i\n", size);

    printf("Fram value: %s\n", frame);

    //isPackage(pbuff) ? printf("Package arrived") : printf("Package did not arrived");


    //    printf("Received frame: %s\n", pbuff);


    /*
    //    int *fd_p;
    //    *fd_p = fd;

        char inpBuf[255];

        //  printf("Enter the input: \n");

          scanf("%s",inpBuf);

          printf("Entered input: %s\n", inpBuf);

          write(fd, inpBuf, 255);

        printf("Transmitted: %s\n", inpBuf);

        //char buff[255];

        char *pbuff;

        //pbuff = &buff;

        pbuff = serialRead(fd);


        printf("Received: %s\n", pbuff);
        //printf("sss: %s\n", "bybys");

        serialClose(fd);*/
    return 0;

}

