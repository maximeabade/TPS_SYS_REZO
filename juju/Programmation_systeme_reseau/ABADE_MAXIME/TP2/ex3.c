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

    //close(p[0]);  
    write(p[1], "Salut" ,sizeof("Salut"));

    return 0;  
}