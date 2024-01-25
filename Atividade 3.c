/*Escreva um programa em C, que teste o funcionamento de cada um dos tipos de scheduling apresentados anteriormente. Utilize 20 iterações para um melhor entendimento*/
#include <stdio.h>

void static_schedule() {
    printf("Executando agendamento estático...\n");
    for(int i = 0; i < 20; i++) {
        printf("Iteração %d\n", i);
    }
}

void dynamic_schedule() {
    printf("Executando agendamento dinâmico...\n");
    for(int i = 0; i < 20; i++) {
        printf("Iteração %d\n", i);
    }
}

void random_schedule() {
    printf("Executando agendamento aleatório...\n");
    for(int i = 0; i < 20; i++) {
        printf("Iteração %d\n", i);
    }
}

void guided_schedule() {
    printf("Executando agendamento guiado...\n");
    for(int i = 0; i < 20; i++) {
        printf("Iteração %d\n", i);
    }
}

void auto_schedule() {
    printf("Executando agendamento automático...\n");
    for(int i = 0; i < 20; i++) {
        printf("Iteração %d\n", i);
    }
}

int main() {
    static_schedule();
    dynamic_schedule();
    random_schedule();
    guided_schedule();
    auto_schedule();

    return 0;
}

/*Escreva um programa em C, com OpenMP, que dado um número maior do que 1.000.000.000 (um bilhão), calcular a soma de todos os seus divisores. 
Utilize os métodos:
Explicitando uma região crítica
Redução com for estático
Redução com for dinâmico*/


#include <stdio.h>
#include <omp.h>

#define NUM 1000000000

long long sum_divisors_critical(long long num) {
    long long sum = 0;
    #pragma omp parallel for
    for (long long i = 1; i <= num; i++) {
        if (num % i == 0) {
            #pragma omp critical
            sum += i;
        }
    }
    return sum;
}

long long sum_divisors_static(long long num) {
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (long long i = 1; i <= num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

long long sum_divisors_dynamic(long long num) {
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (long long i = 1; i <= num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    printf("Soma dos divisores (região crítica): %lld\n", sum_divisors_critical(NUM));
    printf("Soma dos divisores (for estático): %lld\n", sum_divisors_static(NUM));
    printf("Soma dos divisores (for dinâmico): %lld\n", sum_divisors_dynamic(NUM));

    return 0;
}

/*Escreva um programa serial e paralelo em C, com OpenMP, que dado um vetor de inteiros e um valor x, encontrar quantas vezes x ocorre no vetor. Calcular as métricas de desempenho. */


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 1000000
#define X 10

void count_serial(int* arr, int x) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    printf("Serial count: %d\n", count);
}

void count_parallel(int* arr, int x) {
    int count = 0;
    #pragma omp parallel for reduction(+:count)
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    printf("Parallel count: %d\n", count);
}

int main() {
    srand(time(NULL));
    int* arr = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 20;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    count_serial(arr, X);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Serial time: %f\n", cpu_time_used);

    start = clock();
    count_parallel(arr, X);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Parallel time: %f\n", cpu_time_used);

    free(arr);
    return 0;
}

