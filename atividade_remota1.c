#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    float* arr = (float*)malloc(SIZE * sizeof(float));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (float)rand() / RAND_MAX;
    }

    float sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    float mean = sum / SIZE;

    float sq_diff_sum = 0.0;
    #pragma omp parallel for reduction(+:sq_diff_sum)
    for (int i = 0; i < SIZE; i++) {
        sq_diff_sum += (arr[i] - mean) * (arr[i] - mean);
    }
    float variance = sq_diff_sum / SIZE;

    float std_dev = sqrt(variance);

    printf("desvio padrão: %f\n", std_dev);

    free(arr);
    return 0;
}
