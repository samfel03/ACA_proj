#include <immintrin.h>
#include <iostream>
#include <array>
#include <ctime>

#define NPOSLAND 17048

typedef double real;

int main() {

    // Use 256 bit registers and we are storing 64bit doubles in them.
    __m256d _result, _vec;

    std::array<real, NPOSLAND * NPOSLAND> testVector;
    std::array<real, NPOSLAND * NPOSLAND> result;

    srand(time(NULL));

    for (int i = 0; i < NPOSLAND * NPOSLAND; ++i) {
        testVector[i] = ((double) rand() / (RAND_MAX));
    }

    for (int x = 0; x < NPOSLAND; x += 4) {

        // 256bit registers, loading, on packed doubles
        _vec = _mm256_load_pd(&testVector[x]);

        // 256bit registers, multiplication, on packed doubles
        _result = _mm256_mul_pd(_vec, _vec);

        _mm256_store_pd(&result[x], _result);
    }

    printf("Finished");
}