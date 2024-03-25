#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    int fd1;
    int fd2;
    char buf;
    int filesize;
    int i;
    int n;

    if(argc == 3){

        fd1 = open(argv[1], O_RDONLY | O_CREAT);
        fd2 = open(argv[2], O_WRONLY | O_CREAT);

        filesize = lseek(fd1, (off_t) 0, SEEK_END); 
        printf("Source file size is %d\n", filesize);

        for (i = filesize - 1; i >= 0; i--) { //read byte by byte from end
            lseek(fd1, (off_t) i, SEEK_SET);

            n = read(fd1, &buf, 1);
            if (n != 1) {
                fprintf(stderr, "can't read 1 byte");
                exit(-1);
            }

            n = write(fd2, &buf, 1);
            if (n != 1) {
                fprintf(stderr, "can't write 1 byte");
                exit(-1);
            }

        }

        close(fd1);
        close(fd2);

    }
    return(0);
}