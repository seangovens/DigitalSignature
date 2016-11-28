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

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

struct Poly add(struct Poly a, struct Poly b) {
	struct Poly res;
	res.degree = max(a.degree, b.degree);
    int aMinDeg = a.degree - a.sizeCoefs + 1, bMinDeg = b.degree - b.sizeCoefs + 1;
    int minDeg = min(aMinDeg, bMinDeg);
    res.sizeCoefs = res.degree - minDeg + 1;
	res.coefs = malloc(res.sizeCoefs * sizeof(int));
	
    int currDeg = res.degree;
	for (int i = 0; i < res.sizeCoefs; i++) {
		if (currDeg > a.degree || currDeg < aMinDeg)
            *(res.coefs + (i * sizeof(int))) = *(b.coefs + (i * sizeof(int)));
        else if (currDeg > b.degree || currDeg < bMinDeg)
            *(res.coefs + (i * sizeof(int))) = *(a.coefs + (i * sizeof(int)));
        else {
            *(res.coefs + (i * sizeof(int))) = *(a.coefs + (i * sizeof(int)))
                                                + *(b.coefs + (i * sizeof(int)));
        }
        currDeg--;
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
