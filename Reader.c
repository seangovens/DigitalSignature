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
	char buf[129];
	
	int x_arr[16][127];
	int ind = 0;
	
	while (fgets(buf, 129, f)) {
		
		for (int i = 0; i < 129; i++) {
			for (int j = 0; j < 8; j++) {
				x_arr[i / 8][((i % 8) * 8) + j + 63] = (buf[i] >> j) & 1;
			}
		}
		
		// WRITE TO FILE SOMEHOW
		
		/*printf("{");
		for (int i = 0; i < 64; i++) {
			printf(" %d ", *(res + i));
		}
		printf("}\n");*/
		
		ind++;
	}
	
	clock_t st, en;
	st = clock();
	
	for (int i = 0; i < 4096; i++) {
		swifft(x_arr);
	}
	
	en = clock();
	printf("EXECUTION TIME: %f\n", (double) (en - st) / CLOCKS_PER_SEC);
	
	fclose(f); fclose(out);
	
	return 0;
}