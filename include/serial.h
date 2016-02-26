#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int _source;
extern int _destination;
extern int _command;
extern int _status;
extern int  serialInit();
extern void serialClose(int fd);
extern char *serialRead(int fd);

