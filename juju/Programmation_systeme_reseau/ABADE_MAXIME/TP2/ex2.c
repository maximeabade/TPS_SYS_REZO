#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    const int Nbuff =1000;
    char buff[Nbuff]; 
    int p[2], n;

    pipe(p);

    //close(p[1]);
    n = read(p[0], buff, Nbuff-1);  
    buff[n] = '\0';
    printf("%s \n", buff); 

    return 0;  
}