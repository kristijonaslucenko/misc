#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <serial.h>
#include <receiveFrame.h>
#include <packetLogger.h>


int main()
{
    char* pbuff;
    char* frame;

    frame = (char*)malloc(255);

    int fd = serialInit();

    pbuff = serialRead(fd);

    int size;

    size = getPacket(pbuff, frame);

    printf("Size of frame: %i\n", size);

    printf("Frame value: %s\n", frame);



    char* _pSource;
    char* _pDestination;
    char* _pCommand;
    char* _pData;

    _pSource = (char*)malloc(sizeof(char));
    _pDestination = (char*)malloc(sizeof(char));
    _pCommand = (char*)malloc(sizeof(char));
    _pData = (char*)malloc(255);


    int _dataLenght;

    _dataLenght = processPacket(frame, size, _pSource, _pDestination, _pCommand, _pData);


    printf("\n\n_pSource: %s\n", _pSource);
    printf("_pDestination: %s\n", _pDestination);
    printf("_pCommand: %s\n", _pCommand);
    printf("Data lenght: %i\n", _dataLenght);
    printf("Data: %s\n", _pData);

    int packet;
    packet = packetLogger();

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
        //printf("sss: %s\n", "55");

        serialClose(fd);*/
    return 0;

}

