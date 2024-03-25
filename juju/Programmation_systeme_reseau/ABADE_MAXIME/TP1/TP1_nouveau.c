#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int temps;
	
	if (argc != 2) {
		printf("usage: %s <nb_se_secondes>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	temps = atoi(argv[1]);
	printf("Nouveau code du fils\n");
	printf("Duree du sommeil : %d\n", temps);
	sleep(temps);
	printf("Réveil et fin du fils après %d secondes \n", temps);
	return 0;
}
