#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int res, pid, status;
	
	switch(res=fork()) {
		case -1: // le fork a echoue
			printf("fork impossible...\n");
			exit(5);
		case 0: //  Processus fils
			printf("processus fils %d execute ls\n",getpid());
			execlp("/bin/ls", "ls", "-al", NULL);
			fprintf(stderr,"Ce message n'apparait pas si tout va bien ");
			fprintf(stderr,"car le code est changé\n");
			exit(10);
		default:
			pid = wait(&status);	// Le père attend le fils. Wait retourne le pid du fils
			printf("processus père %d\n", getpid());
			printf("PID = %d, status = %d\n", pid, status);
	}
	return 0;
}
