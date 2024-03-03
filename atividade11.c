#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 1000

int main(int argc, char* argv[]) {
    int rank, size, i;
    int vector[SIZE];
    int sum = 0, double_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (i = 0; i < SIZE; i++) {
            vector[i] = rand() % 100;
        }
    }

    MPI_Bcast(vector, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 1) {
        for (i = 0; i < SIZE; i++) {
            sum += vector[i];
        }
    } else if (rank == 2) {
        for (i = 0; i < SIZE; i++) {
            double_sum += 2 * vector[i];
        }
    }

    if (rank == 1) {
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (rank == 2) {
        MPI_Send(&double_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        int received_sum, received_double_sum;
        MPI_Status status;

        MPI_Recv(&received_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&received_double_sum, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);

        printf("Somatório dos elementos do vetor: %d\n", received_sum);
        printf("Somatório do dobro de cada elemento: %d\n", received_double_sum);
    }

    MPI_Finalize();

    return 0;
}
