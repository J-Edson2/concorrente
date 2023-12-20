#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    const int num_samples = 1000000;
    int count_inside = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();

        #pragma omp for reduction(+:count_inside)
        for (int i = 0; i < num_samples; ++i) {
            double x = (rand_r(&seed) % 10000) / 10000.0;
            double y = (rand_r(&seed) % 10000) / 10000.0;

            double distance = x * x + y * y;

            if (distance <= 1.0) {
                count_inside++;
            }
        }
    }

    double pi_approx = 4.0 * count_inside / num_samples;

    printf("Aproximação de PI usando %d amostras: %f\n", num_samples, pi_approx);

    return 0;
}
