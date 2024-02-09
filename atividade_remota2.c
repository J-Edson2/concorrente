#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000
#define SCALAR 10

int main() {
    int* arr = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }

    // Multiplica por um escalar
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        arr[i] *= SCALAR;
    }

    // Encontrar o maior elemento
    int max_val = 0;
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        #pragma omp critical
        {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
    }

    printf("O maior valor é: %d\n", max_val);

    free(arr);
    return 0;
}
