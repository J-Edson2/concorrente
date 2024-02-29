#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i, provided;
    double pi, sum = 0.0, start, end, x, step;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    step = 1.0/(double) size;
    start = rank * step;
    end = start + step;

    for (i = start; i < end; i += step) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("pi is approximately %.16f\n", step * pi);

    MPI_Finalize();

    return 0;
}
