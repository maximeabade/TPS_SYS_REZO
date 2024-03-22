#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    pid_t pid;
    int status;
    pid = fork();
    switch(pid) {
        case 0 : 
        //sleep(15);
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        printf("TACHE F1\n");
        kill(getppid(), SIGCONT);
        kill(pid, SIGSTOP);
        printf("TACHE F2\n");
        kill(getppid(), SIGCONT);
        break;

        case -1 :
        //sleep(15);
        perror("Erreur de création de processus avec fork");
        exit(-1);
        break;

        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        kill(pid, SIGCONT);
        kill(getpid(), SIGSTOP);
        printf("TACHE P1\n");
        kill(pid, SIGCONT);
        kill(getpid(), SIGSTOP);
        printf("TACHE P2\n");
        exit(0);
        break;
    }

    return 0;
}