//Escreva um programa em C, com OpenMP, que encontre o maior valor de um vetor aleatório.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    int* arr = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }

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

//Escreva um programa em C, com OpenMP, que encontre o índice do maior valor de um vetor aleatório.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    int* arr = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }

    int max_val = 0;
    int max_idx = -1;
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        #pragma omp critical
        {
            if (arr[i] > max_val) {
                max_val = arr[i];
                max_idx = i;
            }
        }
    }

    printf("O maior valor é: %d e seu índice é: %d\n", max_val, max_idx);

    free(arr);
    return 0;
}

