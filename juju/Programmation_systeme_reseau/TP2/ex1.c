#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    const int Nbuff =1000;
    char buff[Nbuff]; 
    int fds1[2], fds2[2], pid, n, status;

    pipe(fds1);
    pipe(fds2);

    if((pid=fork())>0){
        //pere
        close(fds1[0]);  
        write(fds1[1], "Salut Fils" ,sizeof("Salut Fils"));

        close(fds2[1]); 
        n = read(fds2[0], buff, Nbuff-1);  
        buff[n] = '\0';
        printf("%s \n", buff); 

        wait(&status);

    } else { 
        //fils
        close(fds1[1]);
        n = read(fds1[0], buff, Nbuff-1);  
        buff[n] = '\0';
        printf("%s \n", buff); 

        close(fds2[0]);
        write(fds2[1], "Salut Pere", sizeof("Salut Pere"));

        exit(0);  
    }
    return 0;  
}