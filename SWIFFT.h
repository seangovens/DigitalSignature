#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define K_POW 15
#define K_VAL 16384

#ifndef SWIFFT_FUNC
#define SWIFFT_FUNC

void freeCoefs(mpz_t a1[], int size);

void evaluate(mpz_t res, mpz_t coefs[], int pow);

void extract(mpz_t R, mpz_t c[]);

short * modReduce(mpz_t c[]);

void printCoefs(mpz_t c[], int size);

short * swifft(char x[], const short a[]);

short * swifft_entry(char buf[1025]);

#endif