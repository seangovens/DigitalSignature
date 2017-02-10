// AVX2 M/C IP :156.59.7.29
#include "SWIFFT.h"

#define SIZE 7

const int N = 4;
const int M = 16;
const int P = 257;

struct Poly {
	int degree;
	int sizeCoefs;
	int firstInd;
	int * coefs;
};

struct Poly new_poly(int d, int s, int f, int * c) {
	struct Poly new;
	new.degree = d;
	new.sizeCoefs = s;
	new.firstInd = f;
	new.coefs = c;
	
	return new;
}

void printCoefs(struct Poly c);

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

struct Poly add(struct Poly a, struct Poly b) {
	struct Poly res;
	res.degree = max(a.degree, b.degree);
	res.firstInd = SIZE - (res.degree + 1);
	int a_first = SIZE - (a.degree + 1), b_first = SIZE - (b.degree + 1);
	res.sizeCoefs = max(a_first + a.sizeCoefs, b_first + b.sizeCoefs) - res.firstInd;
	res.coefs = (int *) calloc(SIZE, sizeof(int));
	
	for (int i = 0; i < a.sizeCoefs; i++) {
		res.coefs[a_first + i] = a.coefs[a.firstInd + i];
	}
	
	for (int i = 0; i < b.sizeCoefs; i++) {
		res.coefs[b_first + i] += b.coefs[b.firstInd + i];
	}
	
	return res;
}

struct Poly sub(struct Poly a, struct Poly b) {
	struct Poly b_1;
	b_1 = new_poly(b.degree, b.sizeCoefs, b.firstInd, (int *) malloc(N * sizeof(int)));
	for (int i = 0; i < b.sizeCoefs; i++) {
		b_1.coefs[b.firstInd + i] = -b.coefs[b.firstInd + i];
	}
	
	struct Poly res = add(a, b_1);
	free(b_1.coefs);
	
	return res;
}

struct Poly karatsuba(struct Poly f, struct Poly g) {
	struct Poly res;
	
	//printf("CURR COEFS: %d\n", f.sizeCoefs);
	
	if (f.sizeCoefs == 1) {
		//printf("F DEG: %d\n", f.degree);
		res = new_poly(f.degree + g.degree, 1, SIZE - ((f.degree + g.degree) + 1), (int *) malloc(SIZE * sizeof(int)));
		res.coefs[res.firstInd] = f.coefs[f.firstInd] * g.coefs[g.firstInd];
		//printf("MUL COEF: %d\n", res.coefs[res.firstInd]);
		//printf("RES COEF: %d, F COEF: %d, G COEF: %d\n", res.coefs[res.firstInd], f.coefs[f.firstInd], g.coefs[g.firstInd]);
		//printf("RES FIRSTIND: %d\n", res.firstInd);
	}
	else {
		int halfCoefs = f.sizeCoefs / 2;
		int halfDeg = f.degree / 2;
		struct Poly uf = new_poly(halfDeg, halfCoefs, f.firstInd, f.coefs);
		struct Poly lf = new_poly(halfDeg, halfCoefs, f.firstInd + halfCoefs, f.coefs);
		//printf("halfCoefs f: %d\n", halfCoefs);
		//printf("f address: %d, lf address: %d\n", f.coefs, lf.coefs);
		
		halfCoefs = g.sizeCoefs / 2;
		halfDeg = g.degree / 2;
		struct Poly ug = new_poly(halfDeg, halfCoefs, g.firstInd, g.coefs);
		struct Poly lg = new_poly(halfDeg, halfCoefs, g.firstInd + halfCoefs, g.coefs);
		//printf("halfCoefs g: %d\n", halfCoefs);
		//printf("g address: %d, lg address: %d\n", g.coefs, lg.coefs);
        
        int n = max(f.degree, g.degree) + 1;
		
		printf("RESULTS OF MUL:\n");
		//printCoefs(uf);
		//printCoefs(ug);
		struct Poly up = karatsuba(uf, ug);
		//printCoefs(up);
		struct Poly low = karatsuba(lf, lg);
		//printCoefs(low);
		
		struct Poly a_1 = add(uf, lf);
		struct Poly a_2 = add(ug, lg);
		struct Poly k_1 = karatsuba(a_1, a_2);
		printCoefs(a_1); printCoefs(a_2);
		printCoefs(k_1);
		struct Poly s_1 = sub(k_1, up), mid = sub(s_1, low);
		printCoefs(s_1);
		printCoefs(mid);
		
		up.degree += n;
        mid.degree += n / 2;
		
		struct Poly resT = add(up, mid);
        res = add(resT, low);
		free(a_1.coefs); free(a_2.coefs); free(k_1.coefs); free(s_1.coefs);
		free(up.coefs); free(low.coefs); free(mid.coefs); free(resT.coefs);
	}
	
	return res;
}

/*void classical(int * res, int f[N], int g[N]) {
	for (int i = 0; i < N; i++) {
		int coef = 0;
		for (int j = 0; j <= i / 2; j++) {
			int k = i - j;
			coef += f[i] * g[j];
            if (i != j) coef += f[j] * g[i];
		}
		*(res + (i * sizeof(int))) = coef;
	}
}*/

void printCoefs(struct Poly c) {
	for (int i = c.firstInd; i < c.firstInd + c.sizeCoefs; i++) {
		printf("At %d: %d\n", i, c.coefs[i]);
	}
	printf("\n");
}

int main(int argc, char * argv[]) {
	int fCoefs[SIZE] = {0, 0, 0, 1, 1, 1, 1};
	struct Poly f = new_poly(3, 4, 3, &fCoefs[0]);
	int gCoefs[SIZE] = {0, 0, 0, 1, 1, 1, 1};
	struct Poly g = new_poly(3, 4, 3, &gCoefs[0]);
	
	struct Poly r = karatsuba(f, g);
	
	printCoefs(r);
	
	free(r.coefs);
    
	return 0;
}
