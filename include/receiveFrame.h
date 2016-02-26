#include <stdbool.h>

extern int getPacket(char* pDataBuffer, char* pPacket);
extern int processPacket(char* ppPacket, int packetSize, char* pSource, char* pDestination, char* pCommand, char* pData);

