#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "swifft.h"
#include "cff.h"
#include "sodium.h"

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

char ** gen_sk() {
}

char ** gen_pk(char ** sk) {
}

// Should return appropriate e such that e choose (e / 2) is greater than 2^num_bits_in_message
int calc_e {
}



char * sign(char * m, size_t num_bytes, char ** sk) {
    int e = calc_e(num_bytes);
    int k = e / 2;
    int * bm = cff_encode(m, num_bytes, e, k);
    
    char * sig = malloc(N * M * sizeof(char));
    
    for (int i = 0; i < k; i++) {
        add_vect(sig, *(sk + *(bm + i)));
    }
    
    return sig;
}

bool verify(char * m, size_t num_bytes, char * sig, char ** pk) {
    int e = calc_e(num_bytes);
    int k = e / 2;
    int * bm = cff_encode(m, num_bytes, e, k);
    
    int * claim = malloc(N * M * sizeof(char));
    
    for (int i = 0; i < k; i++) {
        add_vect_mod(claim, *(pk + *(bm + i)));
    }
    
    int * correct = swifft(sig);
    
    return equals(claim, correct);
}