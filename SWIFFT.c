#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define K_POW 15
#define K_VAL 16384

const int N = 2;
const int M = 16;
const int P = 257;

/* Free memory allocated to an array of integers. Provided array's length
   should correspond to the provided 'size' parameter. */
void freeCoefs(mpz_t a1[], int size) {
	for (int i = 0; i < size; i++) {
		mpz_clear(a1[i]);
	}
}

/* Initialize the gmp integers in the provided array. This array must be of
   length N. */
void initCoefs(mpz_t a1[N]) {
	for (int i = 0; i < N; i++) {
		mpz_init(a1[i]);
	}
}

/* Evaluate the given polynomial (defined by the 'coefs' coefficient array)
   with the input 2^('pow') and store it as an integer in 'res'. */
void evaluate(mpz_t res, mpz_t coefs[N], int pow) {
	int currPow = 0;
	
	for (int i = 0; i < N; i++) {
		mpz_mul_2exp(coefs[i], coefs[i], currPow);
		mpz_add(res, res, coefs[i]);
		currPow += K_POW;
	}
}

/* Extract a polynomial from the given integer and store it as an array of
   coefficients in 'c'. */
void extract(mpz_t R, mpz_t c[(N << 1) - 1]) {
	mp_bitcnt_t b = K_POW;
	
	for (int i = 0; i < (N << 1) - 1; i++) {
		mpz_init(c[i]);
		mpz_fdiv_r_2exp(c[i], R, b);
		if (mpz_cmp_si(c[i], K_VAL) > 0)
			mpz_sub_ui(c[i], c[i], K_VAL);
		
		mpz_sub(R, R, c[i]);
		mpz_fdiv_q_2exp(R, R, b);
	}
}

/* Reduce the given polynomial in 'c' by rducing the entire polynomial by
   (x^N + 1) and then reducing the remaining coefficients by P. */
void modReduce(mpz_t c[(N << 1) - 1]) {
	for (int i = (N << 1) - 2; i > N - 1; i--) {
		mpz_sub(c[i - N], c[i - N], c[i]);
		printf("%d\n", i - N + 1);
		mpz_set_ui(c[i], 0);
	}
	
	for (int i = 0; i < N; i++) {
		mpz_fdiv_r_ui(c[i], c[i], P);
	}
}

void printCoefs(mpz_t c[], int size) {
	printf("{");
	for (int i = 0; i < size; i++) {
		printf(" %d ", mpz_get_si(c[i]));
	}
	printf("}\n");
}

int main(int argc, char * argv[]) {
    mpz_t fCoefs[N]; mpz_t gCoefs[N]; mpz_t F; mpz_t G;
	mpz_init(F); mpz_init(G);
	initCoefs(fCoefs); initCoefs(gCoefs);
	
	evaluate(F, fCoefs, K_POW); evaluate(G, gCoefs, K_POW);
	
	mpz_t R;
	mpz_init(R);
	mpz_mul(R, F, G);
	
	mpz_t rCoefs[(N << 1) - 1];
	extract(R, rCoefs);
	modReduce(rCoefs);
	
	printCoefs(rCoefs, N);
	
	freeCoefs(fCoefs, N); freeCoefs(gCoefs, N); freeCoefs(rCoefs, (N << 1) - 1);
	mpz_clear(F); mpz_clear(G); mpz_clear(R);
	
	return 0;
}
