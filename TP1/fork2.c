#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t p;
    int status;
    p = fork();
    switch(p) {
        case 0 : 
        //sleep(15);
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        break;

        case -1 :
        //sleep(15);
        perror("Erreur de création de processus avec fork");
        exit(-1);
        break;

        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        printf("J'attends la terminaison du fils.\n");
        waitpid(p, &status, WUNTRACED | WCONTINUED);
        printf("La valeur de retour WEXITSTATUS est : %d\n", WEXITSTATUS(status));
        printf("La valeur de retour WIFEXITED est : %d\n", WIFEXITED(status));
        exit(0);
        break;
    }
    return 0;
}