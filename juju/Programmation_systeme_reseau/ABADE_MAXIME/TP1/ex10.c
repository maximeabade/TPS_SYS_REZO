#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int i;
    int status;
    pid_t tab[4];
    if(argc == 5){
        for(i = 0; i<4; i++){
            tab[i] = fork();
            if(tab[i] == 0) {
                printf("Je suis un fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
                exit(atoi(argv[i + 1]));
                break;
            } else {
                printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
                printf("J'attends la terminaison des fils.\n");
                waitpid(tab[i], &status, WUNTRACED | WCONTINUED);
                printf("La valeur de retour du fils est : %d\n", WIFEXITED(status));
            }
        }
    }
    return 0;
}