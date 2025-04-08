#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>

#define NPOSLAND 10000

typedef double real;
using namespace std;

int main() {

    array<real, NPOSLAND * NPOSLAND> testVector;
    array<real, NPOSLAND * NPOSLAND> result;

    srand(time(NULL));

    for (int i = 0; i < NPOSLAND * NPOSLAND; ++i) {
        testVector[i] = ((double) rand() / (RAND_MAX));
    }

    for (int x = 0; x < NPOSLAND; x += 4) {

        for (int i = 0; i < 4; ++i) {
            int index = x + i;
            if (index < NPOSLAND) {
                result[index] = testVector[index] + testVector[index];
            }
        }
    }

    printf("Finished\n");

    return 0;
}
