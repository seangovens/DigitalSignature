#include <stdio.h>
#include <stdlib.h>

const int N = 2;
const int M = 16;
const int P = 257;

void karatsuba(int * res, int f[N], int g[N]) {
    
}

void classical(int * res, int f[N], int g[N]) {
	for (int i = 0; i < N; i++) {
		int coef = 0;
		for (int j = 0; j <= i / 2; j++) {
			int k = i - j;
			coef += f[i] * g[j];
            if (i != j) coef += f[j] * g[i];
		}
		*(res + (i * sizeof(int))) = coef;
	}
}

int main(int argc, char * argv[]) {
	int f[N];
	int g[N];
	f[0] = 1; f[1] = 2;
	g[0] = 3; g[1] = 1;
	int * r = malloc(N * sizeof(int));
	
	classical(r, f, g);
	
	for (int i = 0; i < N; i++) {
		printf("%d\n", *(r + (i * sizeof(int))));
	}
    
    free(r);

	return 0;
}