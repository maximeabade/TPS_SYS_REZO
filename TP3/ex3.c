#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
 
void sig_handler(int signum){
    printf("Réveillez-vous\n");
}
 
int main(){

    int cpt = 0;
    int return_value = -1;
    char question[100];
    struct sigaction action;
    
    action.sa_handler = &sig_handler;

    sigaction(SIGALRM, &action, NULL);
 
    while((cpt < 3) & (return_value == -1)){

        printf("Saisissez une question : \n");
 
        alarm(5);  // Scheduled alarm after 1 second

        return_value = scanf("%s", question);
        
        cpt++;

    }

    if(return_value == -1){
        printf("pas de question, pas de réponse !!\n");
    } else {
        printf("%s\n", question);
    }
    

return 0;
}