#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	pid_t pid;
	char * vecteur[4];
	if (argc != 4) {
		printf("usage: %s <nom_du_programme_calcul> <operande_1> <operande_2>\n", argv[0]);
		exit(10);
	}
	switch(pid=fork()) {
		case -1:
			printf("fork impossible...\n");
			exit(5);
		case 0:
			vecteur[0] = argv[1];
			vecteur[2] = argv[2];
			vecteur[3] = argv[3];
			vecteur[4] = NULL;
			execvp("ls", vecteur);
			printf("Recouvrement du code de %s impossible...", argv[1]);
			exit(15);
		default:
			wait(NULL);
	}
	return 0;
}
