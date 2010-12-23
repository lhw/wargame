/* by lwi */
#include <stdlib.h>
#include <stdio.h>

static char pw[] = "lxcc7EQaMfIeW8Kdxz5I";

int pwcheck(char *input) {
	char *p = pw;
	int res;

	while(p < pw + sizeof(pw) && (res = *(input++) - *(p++)) == 0);
	return res;	
}

int main(int argc, char **argv) {
	if(argc < 2)
		return;
	if(pwcheck(argv[1]) == 0)
		system("/bin/sh");
}
