#include <immintrin.h>
#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>

#define NPOSLAND 10000

typedef float real;
using namespace std;

int main() {

    // Use 256 bit registers and we are storing 64bit doubles in them.
    __m256 _result, _vec;

    real* testVector = static_cast<real*>(std::aligned_alloc(64, NPOSLAND * NPOSLAND * sizeof(real)));
    real* result = static_cast<real*>(std::aligned_alloc(64, NPOSLAND * NPOSLAND * sizeof(real)));

    srand(time(NULL));

    for (int i = 0; i < NPOSLAND * NPOSLAND; ++i) {
        testVector[i] = ((double) rand() / (RAND_MAX));
    }

    for (int x = 0; x < NPOSLAND; x += 8) {

        // 256bit registers, loading, on packed doubles
        _vec = _mm256_load_ps(&testVector[x]);

        // 256bit registers, multiplication, on packed doubles
        _result = _mm256_add_ps(_vec, _vec);

        _mm256_store_ps(&result[x], _result);
    }

    printf("Finished\n");

    std::free(testVector);
    std::free(result);
}