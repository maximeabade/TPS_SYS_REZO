#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int tub;
    char buf[11]; 

    tub = open("myTube", O_WRONLY);

    tub = open("myTube", O_RDONLY);
    read(tub, buf ,sizeof(buf) - 1);
    buf[11]= '\0';
    printf("J'ai lu %s \n", buf);

    write(tub, "0123456789", sizeof("0123456789"));
    
    close(tub);

    return(0);
}