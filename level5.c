/* by lwi */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a > b ? b : a)
#define OFFSET 28

int main(int argc, char **argv, char **envp) {
	{	/* force slot for system() in binary, because address of
			system() in libc contains NUL char, making it
			impossible to use it in an exploit */
		int (*f)(const char *cmd) = &system;
		f = &puts;
	}

	static char str[] = "hello.\n";
	char *p = str, *a;

	if(argc != 2 || strlen(argv[0]) != 7 || strlen(argv[1]) > (OFFSET + 12))
		return -1;
	/* clear the enviroment to make it harder */
	for(; *envp; envp++)
		bzero(*envp, strlen(*envp));
	
	a = argv[0];
	while(*(p++) ^= *(a++));
	bzero(argv[0], 8);

	size_t len = strlen(argv[1]);
	bzero(argv[1], MIN(len, OFFSET));

	char buf[8], i = 'a';
	memcpy(buf, argv[1], len); /* oops */
}
