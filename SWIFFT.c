#include "SWIFFT.h"

const int N = 64;
const int M = 16;
const int P = 257;

const short a_table[16][64] = {
	{125,214,86,102,0,223,223,253,188,63,136,214,7,249,137,73,153,31,35,124,221,85,225,13,84,77,118,254,147,138,217,119,137,157,41,142,15,28,209,16,205,216,150,109,46,179,107,236,100,6,212,111,192,225,13,75,100,177,144,210,199,91,104,163},
	{100,211,170,213,88,216,74,188,52,63,136,126,208,31,119,186,11,102,211,155,223,88,67,246,59,191,111,111,211,90,30,149,132,111,144,219,79,42,166,179,179,97,65,167,199,66,147,143,84,116,181,2,240,228,162,189,66,13,36,136,159,188,160,0},
	{55,190,122,49,177,250,47,11,126,126,95,75,17,203,123,75,52,25,166,133,52,244,86,236,181,139,151,134,171,147,46,138,167,154,254,157,187,134,15,48,214,234,151,204,215,169,71,74,69,105,89,250,198,214,29,252,233,184,166,124,39,115,77,237},
	{199,122,176,203,209,88,238,71,79,116,225,69,219,0,151,235,232,170,15,29,153,203,75,43,154,247,235,101,106,138,158,58,178,163,230,44,102,159,207,118,227,161,103,209,35,38,254,82,178,107,51,31,100,254,105,222,39,244,216,167,171,227,131,174},
	{113,99,105,163,43,23,132,137,84,197,189,137,3,18,164,61,166,100,76,151,228,256,92,14,98,145,58,21,91,143,91,6,56,2,206,48,224,85,151,166,32,255,40,189,85,105,184,256,67,146,125,176,256,97,64,147,115,8,216,80,148,165,30,193},
	{211,18,202,181,150,244,41,26,225,106,129,179,130,126,236,159,245,157,116,72,120,245,107,238,178,60,111,112,73,188,57,137,172,41,181,73,13,41,36,175,161,247,132,118,153,5,172,208,174,221,33,194,107,190,88,78,86,15,143,58,210,7,161,170},
	{173,181,214,6,29,191,164,55,134,2,23,156,160,205,151,134,255,146,44,250,87,24,72,86,131,76,159,69,256,226,43,102,129,52,45,64,129,99,64,176,72,206,73,64,190,5,230,40,28,98,102,77,218,65,31,86,236,231,65,74,11,32,77,202},
	{229,205,40,80,163,229,139,121,187,73,246,218,104,195,133,238,175,4,115,36,41,51,86,205,232,185,103,8,38,220,29,109,213,21,68,129,220,253,218,222,173,7,203,166,5,142,68,168,127,95,112,7,96,135,108,127,172,119,170,143,203,250,32,27},
	{83,224,83,209,124,148,207,148,169,20,203,228,130,45,170,64,129,63,28,40,108,152,105,96,239,40,181,80,71,28,61,236,248,233,186,19,136,41,240,100,20,134,196,163,26,174,128,223,137,5,148,204,51,196,201,117,196,40,29,198,9,207,109,38},
	{36,95,35,116,249,195,191,134,142,87,233,35,167,11,20,142,256,226,26,175,20,208,247,132,155,234,106,166,221,192,62,151,215,60,232,198,251,23,186,86,20,203,134,223,255,23,160,75,100,52,37,47,30,3,109,218,5,96,19,107,148,59,170,185},
	{239,167,108,229,50,27,5,43,227,234,175,253,225,111,4,87,80,157,169,221,155,110,63,89,154,140,86,162,86,172,12,43,62,232,165,226,198,73,193,221,165,230,65,15,130,31,53,169,197,201,161,199,123,68,24,181,44,53,115,51,193,74,138,229},
	{133,204,90,223,42,55,88,209,37,129,134,196,64,59,251,248,47,178,109,244,199,231,237,51,227,139,167,115,79,205,10,241,154,207,239,74,10,214,81,44,116,208,192,124,221,2,33,108,218,196,132,155,1,123,234,241,195,124,164,4,144,184,255,200},
	{249,159,204,149,21,2,215,36,203,29,125,175,214,109,196,62,213,153,122,39,60,251,144,33,152,91,103,54,4,158,41,160,12,191,54,252,53,233,256,11,218,251,82,139,208,199,117,87,231,218,75,167,69,74,75,242,5,234,9,1,165,185,206,229},
	{58,218,153,80,48,58,116,247,221,9,184,24,188,216,38,77,107,133,92,173,58,196,81,210,68,14,69,149,75,126,240,143,221,140,76,71,6,101,148,91,93,49,87,151,154,110,187,160,162,184,146,229,71,160,248,17,186,238,2,43,202,241,96,207},
	{210,137,90,100,186,92,79,74,112,145,72,85,35,5,166,179,35,233,164,3,81,218,102,24,254,123,89,236,62,143,66,113,244,80,221,35,171,126,46,49,149,58,6,113,103,97,206,214,94,170,113,19,65,35,218,94,242,16,162,25,129,131,36,173},
	{87,247,14,80,48,40,204,169,177,188,150,134,200,29,19,210,176,111,254,93,155,115,190,130,133,110,236,194,50,22,47,134,216,152,224,31,14,22,135,77,56,102,191,171,77,60,221,93,57,209,153,158,224,196,219,211,170,190,193,241,88,190,186,193}
};


/* Free memory allocated to an array of integers. Provided array's length
   should correspond to the provided 'size' parameter. */
void freeCoefs(mpz_t a1[], int size) {
	for (int i = 0; i < size; i++) {
		//printf("%d < %d\n", i, size);
		mpz_clear(a1[i]);
	}
}

/* Initialize the gmp integers in the provided array. This array must be of
   length N. */
void initShortCoefs(mpz_t a1[N], const short x[]) {
	for (int i = 0; i < N; i++) {
		//printf("Int iteration %d\n", i);
		mpz_init_set_si(a1[i], x[i]);
	}
	//printf("Int done\n");
}

void initCharCoefs(mpz_t a1[N], char x[]) {
	for (int i = 0; i < N; i++) {
		//printf("Char iteration %d\n", i);
		mpz_init_set_si(a1[i], x[i]);
	}
	//printf("Char done\n");
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

/* Reduce the given polynomial in 'c' by reducing the entire polynomial by
   (x^N + 1) and then reducing the remaining coefficients by P. */
short * modReduce(mpz_t c[(N << 1) - 1]) {
	for (int i = (N << 1) - 2; i > N - 1; i--) {
		mpz_sub(c[i - N], c[i - N], c[i]);
		//printf("%d\n", i - N + 1);
		mpz_set_ui(c[i], 0);
	}
	
	short * ret = malloc(N * sizeof(short));
	
	for (int i = 0; i < N; i++) {
		*(ret + i) = (short) mpz_fdiv_r_ui(c[i], c[i], P);
	}
	
	return ret;
}

void printCoefs(mpz_t c[], int size) {
	printf("{");
	for (int i = 0; i < size; i++) {
		printf(" %d ", mpz_get_si(c[i]));
	}
	printf("}\n");
}

/* Convolve the two given vectors. Each component is calculated modulo our
   prime P. */
short * swifft(char x[], const short a[]) {
	//printf("Ayy started\n");
    mpz_t fCoefs[N]; mpz_t gCoefs[N]; mpz_t F; mpz_t G;
	//printf("Test\n");
	mpz_inits(F, G, NULL);
	//printf("Test 2\n");
	//printf("Ayy done\n");
	
	//printf("Init started\n");
	initCharCoefs(fCoefs, x); initShortCoefs(gCoefs, a);
	//printf("Init done\n");
	
	//printf("Eval started\n");
	evaluate(F, fCoefs, K_POW); evaluate(G, gCoefs, K_POW);
	//printf("Eval done\n");
	
	//printf("Mul started\n");
	mpz_t R;
	mpz_init(R);
	mpz_mul(R, F, G);
	//printf("Mul done\n");
	
	//printf("Extract started\n");
	mpz_t rCoefs[(N << 1) - 1];
	extract(R, rCoefs);
	short * ret = modReduce(rCoefs);
	
	//printf("Extract done\n");
	//printCoefs(rCoefs, N);
	
	//printf("Free started\n");
	freeCoefs(fCoefs, N); freeCoefs(gCoefs, N); freeCoefs(rCoefs, (N << 1) - 1);
	mpz_clear(F); mpz_clear(G); mpz_clear(R);
	//int * ret = malloc(64 * sizeof(int));
	//printf("Free done\n");
	
	return ret;
}

/* Take the given 1KB block and process it according to the SWIFFT specifications. */
short * swifft_entry(char buf[1025]) {
	short * res __attribute__((aligned(16))) = malloc(N * sizeof(int));
	for (int i = 0; i < M; i++) {
		short * temp __attribute__((aligned(16))) = swifft(&buf[i * N], a_table[i]);
		
		for (int j = 0; j < N; j++) {
			//printf("i = %d, j = %d\n", i, j);
			*(res + j) = (*(res + j) + *(temp + j)) % P;
		}
	}
	
	return res;
}