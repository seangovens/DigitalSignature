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
	
	printf("Degree: %d\nSizeCoefs: %d\n", res.degree, res.sizeCoefs);
	
    int currDeg = res.degree;
	for (int i = 0; i < res.sizeCoefs; i++) {
		if (currDeg > a.degree || currDeg < aMinDeg)
            *(res.coefs + (i * sizeof(int))) = *(b.coefs + ((b.degree - currDeg)*sizeof(int)));
        else if (currDeg > b.degree || currDeg < bMinDeg)
            *(res.coefs + (i * sizeof(int))) = *(a.coefs + ((a.degree - currDeg)*sizeof(int)));
        else {
            *(res.coefs + (i * sizeof(int))) = *(a.coefs + ((a.degree - currDeg)*sizeof(int))) 
												+ *(b.coefs + ((b.degree - currDeg)*sizeof(int)));
                                                
            printf("a val: %d at %d b val: %d at %d index: %d\n", *(a.coefs + ((a.degree - currDeg)*sizeof(int))), a.degree - currDeg, *(b.coefs + ((b.degree - currDeg)*sizeof(int))), b.degree - currDeg, i);
        }
        currDeg--;
	}
	
	return res;
}

struct Poly neg(struct Poly a) {
	struct Poly res;
	res.degree = a.degree;
	res.sizeCoefs = a.sizeCoefs;
	res.coefs = (int *) malloc(res.sizeCoefs * sizeof(int));
	
	for (int i = 0; i < res.sizeCoefs; i++) {
		*(res.coefs + (i * sizeof(int))) = -*(a.coefs + (i * sizeof(int)));
	}
	
	return res;
}

struct Poly dsub(struct Poly a, struct Poly d1, struct Poly d2) {
	struct Poly d1Neg = neg(d1);
	struct Poly d2Neg = neg(d2);
	
	struct Poly res1 = add(d1Neg, d2Neg);
	struct Poly res2 = add(res1, a);
	
	free(res1.coefs); free(d1Neg.coefs); free(d2Neg.coefs);
	
	return res2;
}

struct Poly karatsuba(struct Poly f, struct Poly g) {
	struct Poly res;
	
	if (f.sizeCoefs == 1) {
		res.degree = f.degree + g.degree;
		res.sizeCoefs = 1;
		*res.coefs = *f.coefs * *g.coefs;
	}
	else {
		int halfCoefs = f.sizeCoefs / 2;
		int halfDeg = f.degree / 2;
		struct Poly uf; uf.degree = halfDeg; uf.sizeCoefs = halfCoefs; uf.coefs = f.coefs;
		struct Poly lf; lf.degree = halfDeg; uf.sizeCoefs = halfCoefs; lf.coefs = f.coefs + (halfCoefs * sizeof(int));
		
		halfCoefs = g.sizeCoefs / 2;
		halfDeg = g.degree / 2;
		struct Poly ug; ug.degree = halfDeg; ug.sizeCoefs = halfCoefs; ug.coefs = g.coefs;
		struct Poly lg; lg.degree = halfDeg; ug.sizeCoefs = halfCoefs; lg.coefs = g.coefs + (halfCoefs * sizeof(int));
        
        int n = max(f.degree, g.degree);
		
		struct Poly up = karatsuba(uf, ug);
        up.degree += n;
		struct Poly low = karatsuba(lf, lg);
		struct Poly mid = dsub(karatsuba(add(uf, lf), add(ug, lg)), up, low);
        mid.degree += n / 2;
		
		struct Poly resT = add(up, mid);
        res = add(resT, low);
        
        free(resT.coefs);
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
	for (int i = 0; i < c.sizeCoefs; i++) {
		printf("At %d: %d\n", i, *(c.coefs + (i * sizeof(int))));
	}
	printf("\n");
}

int main(int argc, char * argv[]) {
	struct Poly f;
	struct Poly g;
	struct Poly r;
	
	f.degree = 2; g.degree = 1; f.sizeCoefs = 3; g.sizeCoefs = 2;
	printf("%d\n", f.sizeCoefs * sizeof(int));
	f.coefs = (int *) malloc((f.sizeCoefs+sizeof(int)) * sizeof(int));
	g.coefs = (int *) malloc((g.sizeCoefs/*+sizeof(int)*/) * sizeof(int));
	int * test = malloc(sizeof(int));
	
	printf("Addresses f: %d %d %d\nAddresses g: %d %d\n", f.coefs + (0 * sizeof(int)), f.coefs + (1 * sizeof(int)), f.coefs + (2 * sizeof(int)), g.coefs + (0 * sizeof(int)), g.coefs + (1 * sizeof(int)));
	printf("Test address: %d\n", test);
	
	*f.coefs = 1; *(f.coefs + sizeof(int)) = 4; *(f.coefs + (2 * sizeof(int))) = 1;
	printCoefs(f);
	*g.coefs = 2; *(g.coefs + sizeof(int)) = 1;
	printCoefs(f);
	printCoefs(g);
	//classical(r, f, g);
	
	printf("Size: %d\n", sizeof(int));
	
	r = add(f, g);
	
	for (int i = 0; i < r.sizeCoefs; i++) {
		printf("%d\n", *(r.coefs + (i * sizeof(int))));
	}
    
    free(f.coefs); free(g.coefs); free(r.coefs);

	return 0;
}
