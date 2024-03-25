#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static void deroute_SIGTERM() {
    printf("Message SIGTERM\n");
}

static void deroute_SIGKILL() {
    printf("Message SIGKILL\n");
}

int main(){
    pid_t p;
    int status;
    p = fork();
    switch(p) {
        case 0 : 
        //sleep(15);
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        printf("J'envoie les signaux à mon père.\n");
        kill(getppid(), SIGTERM);
        kill(getppid(), SIGKILL);
        break;

        case -1 :
        //sleep(15);
        perror("Erreur de création de processus avec fork");
        exit(-1);
        break;

        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        printf("Je déroute les signaux SIGTERM et SIGKILL.\n");
        struct sigaction action;
        memset(&action, '\0', sizeof(action));
        action.sa_handler = &deroute_SIGTERM;
        if(sigaction(SIGTERM, &action, NULL) < 0){
            printf("Erreur sigaction\n");
        }
        action.sa_handler = &deroute_SIGKILL;
        if(sigaction(SIGKILL, &action, NULL) < 0){
            printf("Erreur sigaction\n");
        }
        printf("J'attends la terminaison du fils.\n");
        wait(&status);
        exit(0);
        break;
    }
    return 0;
}