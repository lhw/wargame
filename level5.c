/* by lwi */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t crc32(unsigned char *input) {
	uint32_t result = ~0, xormask[] = { 0x00000000, 0xedb88320 }, length = strlen(input), i;
	
	while(length--) {
		result ^= *(input++);
		for(i = 0; i < 8; i++)
			result = (result >> 1) ^ xormask[result & 1];
	}

	return ~result;
}

int bf(char *input, char *output, unsigned int output_len) {
#define MAX_LOOP_NESTING 100
	char data[2001];
	unsigned int p = 0; /* data pointer */
	unsigned int pc; /* program counter */
	static unsigned long max_iterations = 100000;
	unsigned long length = strlen(input);
	unsigned int wp = 0; /* output pointer */
	unsigned int open_brackets = 0; /* important for loop handling */
	unsigned int nesting_depth = 0;
	unsigned int startpoint[nesting_depth];

	bzero(data, sizeof(data));
	for(pc = 0; pc < length && --max_iterations; pc++) {
		switch(input[pc]) {
			case '<':
				if(p) --p; break;
			case '>':
				if(p < 2000) ++p; break;
			case '+':
				++data[p]; break;
			case '-':
				--data[p]; break;
			case '.':
				if(wp < output_len) output[wp++] = data[p]; break;
			case '[': /* loop start */
				open_brackets = 1;
				if(data[p])
					if(nesting_depth < MAX_LOOP_NESTING)
						break;
					else
						startpoint[++nesting_depth] = (pc + 1 == length) ? pc : pc + 1;
				else
					while(open_brackets && ++pc < length) 
						if(input[pc] == '[') ++open_brackets;
						else if(input[pc] == ']') --open_brackets;
				break;
			case ']': /* loop end */
				if(nesting_depth)
					if(!data[p])
						--nesting_depth;
					else
						pc = startpoint[nesting_depth];
				break;
		}
	}
	return wp;
}

int main(int argc, char **argv) {
	char output1[200];
	char output2[200];

	if(argc < 3)
		return -1;

	bzero(output1, sizeof(output1));
	bzero(output2, sizeof(output2));

	char *wanted[] = {
		"we come in peace",
		"all ur base r teh belong to us"
	};

	int wb1 = bf(argv[1], output1, sizeof(output1));
	int wb2 = bf(argv[2], output2, sizeof(output2));
	
	uint32_t cksum[2] = {
		crc32(argv[1]),
		crc32(argv[2])
	};
	printf("program 1 (%x):\n%s\n\nprogram 2 (%x):\n%s\n\n", cksum[0], output1, cksum[1], output2);
	if(strcmp(wanted[0], output1) == 0 && strcmp(wanted[1], output2) == 0 && cksum[0] == cksum[1])
		system("/bin/sh");
}
