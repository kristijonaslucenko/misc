#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <serial.h>
#include <serial_def.h>

volatile char arrivedByte;
volatile bool packageArrival = false;
volatile bool packageArrived = false;
bool datastart = false;

char dataArrived[100];
char source[3];
char destination[3];
char command[3];
char dataLenght[5];
char checksum[4];
int dl;
char actualData[100];
int _source;
int _destination;
int _command;
int _status;


int getPacket(char* pDataBuffer, char* pPacket);
int processPacket(char* pPacket, char* pSource, char* pDestination, char* pCommand, char* pData);



int getPacket(char* pDataBuffer, char* pPacket)
{
    int startChar = -1;
    int endChar = -1;

    int i = 0;

    while (pDataBuffer[i] != 0)
    {
        if (pDataBuffer[i] == START_CHAR)
            startChar = i;
        else if (pDataBuffer[i] == END_CHAR)
            endChar = i;

        ++i;
    }

    if (startChar != -1 && endChar != -1 && startChar < endChar)
    {
        // +1 and -1 to eliminate start & end characters.
        strncpy(pPacket, pDataBuffer + startChar + 1, endChar - startChar - 1);
        return endChar - startChar - 1;
    }

    return 0;
}


bool receivePackage(char* frame)
{

    _source = 0;
    _destination = 0;
    _command = 0;
    //set a null terminators so the arrays later could be interpreted as a string
    memset(source, '\0', 3);
    memset(destination, '\0', 3);
    memset(command, '\0', 3);
    memset(dataLenght, '\0', 5);
    memset(actualData, '\0', 100);
    memset(checksum, '\0', 4);

    //copy package contents to package fields
    memcpy(source, dataArrived, 2);
    memcpy(destination, dataArrived + 2, 2);
    memcpy(command, dataArrived + 4, 2);
    memcpy(dataLenght, dataArrived + 6, 4);

    //count data bytes and copy data to package data field
    dl = atoi(dataLenght);

    memcpy(actualData, dataArrived + 10, dl);
    memcpy(checksum, dataArrived + (10 + dl), 3);


    _source = atoi(source);
    _destination = atoi(destination);
    _command = atoi(command);
    packageArrived = false;
    packageArrival = false;
    memset(dataArrived, '\0', 100);
    return false;
}
