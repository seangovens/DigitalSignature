#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SWIFFT.h"

int main(int argc, char * argv[]) {
	if (argc != 2) {
		printf("Usage: Reader filename\n");
		return 1;
	}
	
	FILE * f;
	FILE * out;
	
	f = fopen(argv[1], "r");
	char buf[1025];
	
	clock_t st, en;
	st = clock();
	
	while (fgets(buf, 1025, f)) {
		short * res = swifft_entry(buf);
		
		// WRITE TO FILE SOMEHOW
		
		/*printf("{");
		for (int i = 0; i < 64; i++) {
			printf(" %d ", *(res + i));
		}
		printf("}\n");*/
		
		free(res);
	}
	
	en = clock();
	printf("EXECUTION TIME: %f\n", (double) (en - st) / CLOCKS_PER_SEC);
	
	fclose(f); fclose(out);
	
	return 0;
}