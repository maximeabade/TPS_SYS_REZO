#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    int fd1;
    int fd2;
    unsigned char buffer[10];
    int bytes_read;
    int bytes_write;

    if(argc == 3){

        fd1 = open(argv[1], O_RDONLY | O_CREAT);
        fd2 = open(argv[2], O_WRONLY | O_CREAT);

        do {
            bytes_read = read(fd1, buffer, 10); 
            bytes_write = write(fd2, buffer, 10);
        }
        while (bytes_read != 0); 

        close(fd1);
        close(fd2);

    }
    return(0);
}