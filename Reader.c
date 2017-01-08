#include <stdio.h>
#include <stdlib.h>
#include "SWIFFT.h"

int main(int argc, char * argv[]) {
	if (argc != 2) printf("Usage: Reader filename\n");
	
	FILE * f;
	FILE * out;
	
	f = fopen(argv[1], "r");
	char buf[1025];
	
	printf("PROGRAM HAS STARTED!!!\n");
	
	while (fgets(buf, 1025, f)) {
		int * res = swifft_entry(buf);
		printf("TESTERONI\n");
		
		printf("{");
		for (int i = 0; i < 64; i++) {
			printf(" %d ", *(res + (i * sizeof(int))));
		}
		printf("}\n");
		
		free(res);
	}
	
	fclose(f); fclose(out);
}