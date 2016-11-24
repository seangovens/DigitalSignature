#include <stdio.h>
#include <stdlib.h>

const int N = 2;
const int M = 16;
const int P = 257;

struct Poly {
	int degree;
	int sizeCoefs;
	int * coefs;
};

struct Poly add(struct Poly a, struct Poly b) {
	
	//FIX
	struct Poly res;
	//res.degree = a.degree;
	res.coefs = malloc(res.degree * sizeof(int));
	
	for (int i = 0; i < a.sizeCoefs; i++) {
		*(res.coefs + (i * sizeof(int))) = *(a.coefs + (i * sizeof(int)))
											+ *(b.coefs + (i * sizeof(int)));
	}
}

struct Poly dsub(struct Poly a, struct Poly d1, struct Poly d2) {
	struct Poly res;
	res.degree = a.degree;
}

struct Poly karatsuba(struct Poly f, struct Poly g) {
	if (n == 2) {
		
	}
	
	struct Poly a = karatsuba(uf, ug);
	struct Poly d = karatsuba(lf, lg);
	struct Poly e = dsub(karatsuba(add(uf, lf), add(ug, lg)), a, d);
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

int main(int argc, char * argv[]) {
	struct Poly f;
	struct Poly g;
	
	f.degree = N; g.degree = N; f.sizeCoefs = N; g.sizeCoefs = N;
	
	//classical(r, f, g);
	
	
	
	for (int i = 0; i < N; i++) {
		printf("%d\n", *(r + (i * sizeof(int))));
	}
    
    free(r);

	return 0;
}
