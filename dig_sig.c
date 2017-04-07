#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "swifft.h"
#include "cff.h"
#include "sodium.h"

#define SIZE_MESS 1
#define NM 1024

void gen_bin_short(unsigned short x[], int size) {
    for (int i = 0; i < size; i++) {
        x[i] = (unsigned short) (rand() % 2);
    }
}

void gen_bin(unsigned char x[], int size) {
    for (int i = 0; i < size; i++) {
        x[i] = (unsigned char) (rand() % 2);
    }
}

/*char ** gen_sk(int e) {
    char ** sk = malloc(e * sizeof(char *));
    for (int i = 0; i < e; i++) 
}

char ** gen_pk(char ** sk, int e) {
}*/

// Should return appropriate e such that e choose (e / 2) is greater than 2^num_bits_in_message
/*int calc_e(int num_bits) {
    int val = 2;
    int lim = (int) pow(2, num_bits);
    while (comb(val, val / 2) < lim) val++;
    
    return val;
}*/

char * sign(char * m, size_t num_bits) {
    int e = calc_e(num_bits);
    int k = e / 2;
    int * bm = cff_encode(m, num_bytes, e, k);
    
    char * sig = malloc(N * M * sizeof(char));
    
    for (int i = 0; i < k; i++) {
        //add_vect(sig, *(sk + *(bm + i)));
        for (int j = 0; j < 1024; j++) {
            int placeholder = i + j;
        }
    }
    
    return sig;
}

/*bool verify(char * m, size_t num_bytes, char * sig, char ** pk) {
    int e = calc_e(num_bytes);
    int k = e / 2;
    int * bm = cff_encode(m, num_bytes, e, k);
    
    int * claim = malloc(N * M * sizeof(char));
    
    for (int i = 0; i < k; i++) {
        add_vect_mod(claim, *(pk + *(bm + i)));
    }
    
    int * correct = swifft(sig);
    
    return equals(claim, correct);
}*/

int main(int argc, char * argv[]) {
	char m[SIZE_MESS];
    
    char * sig = sign(m, SIZE_MESS * 8);
    
    free(sig);
	
	return 0;
}