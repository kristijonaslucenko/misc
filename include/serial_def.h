//Serial settings

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyUSB0"

#define _POSIX_SOURCE 1 /* POSIX compliant source */


//Packet configuration

#define PACK_START_CHAR '-'
#define PACK_END_CHAR '*'

#define PACK_DATA_LENGHT 255
#define PACK_SOURCE_LENGHT 3
#define PACK_DEST_LENGHT 3
#define PACK_CHECKSUM_LENGHT 4
