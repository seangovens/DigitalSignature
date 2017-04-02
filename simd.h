#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

union Vec8i {
    __m256i m_vec;
    int elem[8];
};

union Vec16c {
    __m256i m_vec;
    char elem[16];
};
