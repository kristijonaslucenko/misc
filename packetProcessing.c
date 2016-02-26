#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <serial.h>
#include <serial_def.h>


int getPacket(char* pDataBuffer, char* pPacket);
int processPacket(char* pPacket, int packetSize, char* pSource, char* pDestination, char* pCommand, char* pData);



int getPacket(char* pDataBuffer, char* pPacket)
{
    int startChar = -1;
    int endChar = -1;

    int i = 0;

    while (pDataBuffer[i] != 0)
    {
        if (pDataBuffer[i] == PACK_START_CHAR)
            startChar = i;
        else if (pDataBuffer[i] == PACK_END_CHAR)
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


int processPacket(char* ppPacket, int packetSize, char* pSource, char* pDestination, char* pCommand, char* pData)
{

    char source[PACK_SOURCE_LENGHT];
    char destination[PACK_DEST_LENGHT];
    char command[PACK_COMM_LENGHT];
    char dataLenghtPkg[PACK_DATA_LENGHT];
    char data[255];
    char checksum[PACK_CHECKSUM_LENGHT];

    int dataLenght;


    //set a null terminators so the arrays later could be interpreted as a string
    memset(source, '\0', PACK_SOURCE_LENGHT);
    memset(destination, '\0', PACK_DEST_LENGHT);
    memset(command, '\0', PACK_COMM_LENGHT);
    memset(dataLenghtPkg, '\0', PACK_DATA_LENGHT);

    //check the packetSize and how to define that
    memset(data, '\0', packetSize);
    memset(checksum, '\0', PACK_CHECKSUM_LENGHT);

    //copy package contents to package fields
    memcpy(source, ppPacket, PACK_SOURCE_LENGHT - 1);
    memcpy(destination, ppPacket + PACK_SOURCE_LENGHT -1, PACK_DEST_LENGHT - 1);
    memcpy(command, ppPacket + PACK_SOURCE_LENGHT + PACK_DEST_LENGHT - 2, PACK_COMM_LENGHT - 1);
    memcpy(dataLenghtPkg, ppPacket + PACK_SOURCE_LENGHT + PACK_DEST_LENGHT + PACK_COMM_LENGHT - 3, PACK_DATA_LENGHT - 1);
    //printf("source: %s\n", dataLenghtPkg);

    //count data bytes and copy data to package data field
    dataLenght = atoi(dataLenghtPkg);
    //
    memcpy(data, ppPacket + PACK_SOURCE_LENGHT + PACK_DEST_LENGHT + PACK_COMM_LENGHT + PACK_DATA_LENGHT - 5, dataLenght);
    memcpy(checksum, ppPacket + (PACK_SOURCE_LENGHT + PACK_DEST_LENGHT + PACK_COMM_LENGHT + PACK_DATA_LENGHT - 4 + dataLenght), PACK_CHECKSUM_LENGHT - 1);

    //Checksum checking is missing since the method is unknown

    strncpy(pSource,source, PACK_SOURCE_LENGHT);
    strncpy(pDestination, destination, PACK_DEST_LENGHT);
    strncpy(pCommand, command, PACK_COMM_LENGHT);
    strncpy(pData, data, dataLenght);

    return dataLenght;
}
