#include <stdio.h>
#include <stdlib.h>

int packetLogger(void) {

    FILE * fp;

   fp = fopen ("./logs/log.txt", "w+");
   fprintf(fp, "test");

   fclose(fp);

   return(0);
}
