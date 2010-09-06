/* by lwi */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

main(int argc, char **argv) {
	char buf[1024];
	int magic = 23;

	if(argc < 2)
		return -1;
	printf("%x\n", &magic);
	strncpy(buf, argv[1], sizeof(buf) - 1);
	printf(buf);
	if(magic == 1337)
		system("/bin/sh");
	
	return 0;
}
