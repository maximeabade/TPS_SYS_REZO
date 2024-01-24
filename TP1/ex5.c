#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t p;
    p = fork();
    printf("Valeur de fork = %d.\n", p);
    switch(p) {
        case 0 : 
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        break;

        case -1 :
        perror("Erreur de création de processus avec fork");
        break;

        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        break;
    }
    return 0;
}