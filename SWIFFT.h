#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>
#include <pthread.h>

#define N 64
#define M 16
#define P 257
#define NUM_COEFS 127

inline void wannamethod_sse(short c[NUM_COEFS], short x[], short a[]) {
    //int num_add = 0;
	for (int i = 0; i < N; i++) {
        if (x[i] == 0) continue;
		for (int j = 0; j < N; j+= 8) {
            __m128i a_vec = _mm_load_si128(a + j);
            __m128i c_vec = _mm_loadu_si128(c + i + j);
            c_vec = _mm_add_epi16(a_vec, c_vec);
            _mm_storeu_si128(c + i + j, c_vec);
            //num_add++;
		}
	}
    //printf("%d\n", num_add);
}

inline void wannamethod_avx(short c[NUM_COEFS], short x[], short a[]) {
        //int num_add = 0;
	for (int i = 0; i < N; i++) {
        if (x[i] == 0) continue;
		for (int j = 0; j < N; j+= 16) {
            __m256i a_vec = _mm256_load_si256(a + j);
            __m256i c_vec = _mm256_loadu_si256(c + i + j);
            c_vec = _mm256_add_epi16(a_vec, c_vec);
            _mm256_storeu_si256(c + i + j, c_vec);
            //num_add++;
		}
	}
    //printf("%d\n", num_add);
}

void swifft(int x_arr[16][127]);