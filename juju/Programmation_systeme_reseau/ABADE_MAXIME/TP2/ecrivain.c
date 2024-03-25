#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    mode_t mode; 
    int tub;
    mode = S_IRUSR | S_IRGRP | S_IWUSR  | S_IWGRP;  
    char buf[11]; 

    mkfifo("myTube", mode);
    tub = open("myTube", O_WRONLY);
    write(tub, "0123456789", sizeof("0123456789"));

    tub = open("myTube", O_RDONLY);
    read(tub, buf ,sizeof(buf) - 1);
    buf[11]= '\0';
    printf("J'ai lu %s \n", buf);
    
    unlink("myTube");

    return(0);
}