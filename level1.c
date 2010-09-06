/* (c) 2010 by lwi@ring0.de */
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {
	char buffer[8];
	int i = 2;

	if(argc < i)
		return -1;
	printf("%x\n", envp[0]);
	strcpy(buffer, argv[1]);
}
