#include <cstdio>
#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <random>

// COMPILATION
    // mpic++ pi.cpp -o pi.x

// EXECUTION 1: to generate the file to plot speed up and efficiency
    // for ((np=1; np<=33; np+=2)); do (time -p mpirun -np $np --oversubscribe ./pi.x 1200000000 > /dev/null) 2>&1 | awk -v np=$np '/real/ {print np, $0}' >> times.txt; done

// EXECUTION 2: to generate the file to plot relative error
    // for N in 1000 5000 10000 50000 100000 500000 1000000 5000000 10000000 50000000 100000000 500000000 1200000000; do mpirun -np 4 ./pi.x $N > /dev/null >> deltas.txt; done

int samples_parallel(int N, int pid, int np);

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int pid, np;

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    const int N = std::stoi(argv[1]);;
    int nc = samples_parallel(N, pid, np);
    double pi;
    double relative_difference;

    if (0 == pid) {
  
        int buffer;

        for (int opid = 1; opid < np; ++opid) {
            MPI_Recv(&buffer, 1, MPI_INT, opid, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            nc += buffer;
        }

        pi = 4.0 * (double) nc / (double) N;
        relative_difference = std::abs(1.0 - (pi / M_PI));

        std::cout << N << " ";
        std::cout << std::scientific << std::setprecision(15) << pi << " ";
        std::cout << std::scientific << std::setprecision(15) << relative_difference << std::endl;
    } 
    else {
        MPI_Send(&nc, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
    return 0;
}

int samples_parallel(int N, int pid, int np)
{
    int n = N / np;
    int count = 0;
    int seed = pid;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    for (int ii = 0; ii < n; ++ii) {
        double rx = dis(gen);
        double ry = dis(gen);
        if (rx * rx + ry * ry < 1.0)
            count++;
    }
    return count;
}
