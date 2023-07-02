#include <mpi.h>
#include <vector>
#include <stdio.h> 
#include <iostream>
#include <fstream> 

void matrix_parallel(int N, int pid, int np)
{
    int m = N / np; // rows
    int n = N; // cols

    std::vector<std::vector<int>> matrix;
    matrix.resize(m, std::vector<int>(n, 0));

    int total = 0;
    for (int i = 0; i < m; i++) {
        int row = i;
        int col = pid * m + i;
        int value = col + 1;
        matrix[row][col] = value;
        total += value;
    }

    int diagonal = 0;

    if (0 == pid) {
        // recv
        std::vector<std::vector<int>> buffer_matrix;
        buffer_matrix.resize(m, std::vector<int>(n, 0));
        int diaglocal;
        for (int opid = 1; opid < np; ++opid) {
            MPI_Recv(&buffer_matrix[0][0], m * n, MPI_INT, opid , 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&diaglocal, 1, MPI_INT, opid , 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            diagonal += diaglocal;
        }
        
        // Print diagonal sum to console
        std::cout << "Diagonal Sum: " << diagonal << std::endl;
        /*
        // Write buffer_matrix to file row by row
        std::ofstream outfile("buffer_matrix.txt");
        if (outfile.is_open()) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    outfile << buffer_matrix[i][j] << " ";
                }
                outfile << std::endl;
            }
            outfile.close();
        } else {
            std::cerr << "Unable to open file." << std::endl;
        }
        */
    } else {
        // send
        MPI_Send(&matrix[0][0], m * n, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Send(&total, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int pid, np;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int N;

    if (pid == 0) {
        // Process 0 reads N from console
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <N>" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        N = std::stoi(argv[1]);
    }

    // call matrix_parallel function
    matrix_parallel(N, pid, np);

    MPI_Finalize();

    return 0;
}



