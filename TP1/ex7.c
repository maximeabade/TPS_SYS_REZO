#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t p;
    int x = 2;
    p = fork();
    switch(p) {
        case 0 : 
        //sleep(15);
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        x += 3;
        break;

        case -1 :
        //sleep(15);
        perror("Erreur de création de processus avec fork");
        break;

        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        x *= 5;
        break;
    }
    printf("Mon uid : %d.\n", getuid());
    printf("Mon gid : %d.\n", getgid());
    printf("Fin du processus %d\n", getpid());
    printf("La variable x vaut %d.\n\n", x);
    return 0;
}