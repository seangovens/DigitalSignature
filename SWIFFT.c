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
    int aMinDeg = a.degree - a.sizeCoefs + 1, bMinDeg = b.degree - b.sizeCoefs + 1;
    int minDeg = min(aMinDeg, bMinDeg);
    res.sizeCoefs = res.degree - minDeg + 1;
    //printf("BEFORE %d\n", res.sizeCoefs);
	res.coefs = (int *) malloc(res.sizeCoefs * sizeof(int));
	//printf("AFTER\n");
	
	//printf("Degree: %d\nSizeCoefs: %d\n", res.degree, res.sizeCoefs);
	
    int currDeg = res.degree;
	for (int i = 0; i < res.sizeCoefs; i++) {
		if (currDeg > a.degree || currDeg < aMinDeg)
            *(res.coefs + i) = *(b.coefs + (b.degree - currDeg));
        else if (currDeg > b.degree || currDeg < bMinDeg)
            *(res.coefs + i) = *(a.coefs + (a.degree - currDeg));
        else {
            *(res.coefs + i) = *(a.coefs + (a.degree - currDeg)) 
												+ *(b.coefs + (b.degree - currDeg));
                                                
            //printf("a val: %d at %d b val: %d at %d index: %d\n", *(a.coefs + ((a.degree - currDeg)*sizeof(int))), a.degree - currDeg, *(b.coefs + ((b.degree - currDeg)*sizeof(int))), b.degree - currDeg, i);
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
		*(res.coefs + i) = -*(a.coefs + i);
	}
	
	return res;
}

struct Poly dsub(struct Poly a, struct Poly d1, struct Poly d2) {
	struct Poly d1Neg = neg(d1);
	struct Poly d2Neg = neg(d2);
	
	struct Poly res1 = add(d1Neg, d2Neg);
	struct Poly res2 = add(res1, a);
	
	//printf("%d %d %d\n", res1.coefs, d1Neg.coefs, d2Neg.coefs);
	free(res1.coefs); free(d1Neg.coefs); //free(d2Neg.coefs);
	
	return res2;
}

struct Poly karatsuba(struct Poly f, struct Poly g) {
	struct Poly res;
	
	//printf("CURR COEFS: %d\n", f.sizeCoefs);
	
	if (f.sizeCoefs <= 1) {
		//printf("End recursion\n");
		res.degree = f.degree + g.degree;
		res.sizeCoefs = 1;
		res.coefs = malloc(sizeof(int));
		*res.coefs = *f.coefs * *g.coefs;
	}
	else {
		int halfCoefs = f.sizeCoefs / 2;
		int halfDeg = f.degree / 2;
		struct Poly uf; uf.degree = halfDeg; uf.sizeCoefs = halfCoefs; uf.coefs = f.coefs;
		struct Poly lf; lf.degree = halfDeg; lf.sizeCoefs = halfCoefs; lf.coefs = f.coefs + halfCoefs;
		//printf("halfCoefs f: %d\n", halfCoefs);
		//printf("f address: %d, lf address: %d\n", f.coefs, lf.coefs);
		
		halfCoefs = g.sizeCoefs / 2;
		halfDeg = g.degree / 2;
		struct Poly ug; ug.degree = halfDeg; ug.sizeCoefs = halfCoefs; ug.coefs = g.coefs;
		struct Poly lg; lg.degree = halfDeg; lg.sizeCoefs = halfCoefs; lg.coefs = g.coefs + halfCoefs;
		//printf("halfCoefs g: %d\n", halfCoefs);
		//printf("g address: %d, lg address: %d\n", g.coefs, lg.coefs);
        
        int n = max(f.degree, g.degree) + 1;
		
		struct Poly up = karatsuba(uf, ug);
		struct Poly low = karatsuba(lf, lg);
		struct Poly mid = dsub(karatsuba(add(uf, lf), add(ug, lg)), up, low);
		up.degree += n;
        mid.degree += n / 2;
		
		struct Poly resT = add(up, mid);
        res = add(resT, low);
        
		//printCoefs(res);
		
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
		printf("At %d: %d\n", i, *(c.coefs + i));
	}
	printf("\n");
}

int main(int argc, char * argv[]) {
	struct Poly f;
	struct Poly g;
	struct Poly r;
	
	f.degree = 3; g.degree = 3; f.sizeCoefs = 4; g.sizeCoefs = 4;
	//printf("%d\n", f.sizeCoefs * sizeof(int));
	f.coefs = (int *) malloc(f.sizeCoefs * sizeof(int));
	g.coefs = (int *) malloc(g.sizeCoefs * sizeof(int));
	//int * test = malloc(sizeof(int));
	
	//printf("Addresses f: %d %d %d\nAddresses g: %d %d\n", f.coefs + (0 * sizeof(int)), f.coefs + (1 * sizeof(int)), f.coefs + (2 * sizeof(int)), g.coefs + (0 * sizeof(int)), g.coefs + (1 * sizeof(int)));
	//printf("Test address: %d\n", test);
	
	*f.coefs = 1; *(f.coefs + 1) = 4; *(f.coefs + 2) = 1; *(f.coefs + 3) = 4;
	//printCoefs(f);
	*g.coefs = 2; *(g.coefs + 1) = 1; *(g.coefs + 2) = 3; *(g.coefs + 3) = 2;
	printCoefs(f);
	printCoefs(g);
	//classical(r, f, g);
	
	//printf("Orig f address: %d\n", f.coefs);
	//printf("Orig g address: %d\n", g.coefs);
	
	r = karatsuba(f, g);
	//printf("END\n");
	
	printCoefs(r);
    
    free(f.coefs); free(g.coefs); free(r.coefs);

	return 0;
}
