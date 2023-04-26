#include <eigen3/Eigen/Dense>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <cstdlib>

void matmul_eigen(int size, int nreps);
void matmul_simple(int size, int nreps);
void fill(std::vector<double> & mat);

int main(int argc, char ** argv)
{
    // read params
    if (argc != 4) {
        std::cerr << "Error. Usage: \n" << argv[0] << "E N I\n";
        std::cerr << "E: Eigen: [1] YES, [0] NO\n";
        std::cerr << "N: Matrix Size\n";
        std::cerr << "I: Iterations\n";
        return 1;
    }
    const int E = std::stoi(argv[1]); // Eigen
    const int N = std::stoi(argv[2]); // Matrix Size
    const int I = std::stoi(argv[3]); // Iterations

    if (E == 1) {
        matmul_eigen(N, I);
    }
    else {
        matmul_simple(N, I);
    }

  return 0;
}

void fill(std::vector<double> & mat) {
    for (auto & val : mat) {
        val = -1.0 + 2.0 * drand48(); // assign a random value between -1 and 1.
    }
}

void matmul_simple(int size, int nreps)
{
  // cummulative time
  double wall_time = 0.0;
  double squared_wall_time = 0.0;
  double cpu_time = 0.0;
  double squared_cpu_time = 0.0;

  for (int ii = 0; ii < nreps; ++ii) {
    // set a new seed
    srand48(ii);

    // create matrices as 1D arrays
    std::vector<double> A(size * size), B(size * size), C(size * size);
    fill(A); fill(B);

    // start time measure
    auto start = std::chrono::steady_clock::now(); // wall clock
    std::clock_t c1 = std::clock(); // cpu clock

    // computation
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }

    double tmp = C[0]; // force computation

    // end time measure
    auto end = std::chrono::steady_clock::now(); // wall clock
    std::clock_t c2 = std::clock(); // cpu clock

    std::clog << tmp << std::endl;

    // accumulate measured time
    double aux_cpu_time = 1.0 * (c2 - c1) / CLOCKS_PER_SEC;
    std::chrono::duration<double> elapsed_seconds = end - start;
    double aux_wall_time = elapsed_seconds.count();
    wall_time += aux_wall_time;
    squared_wall_time += aux_wall_time * aux_wall_time;
    cpu_time += aux_cpu_time;
    squared_cpu_time += aux_cpu_time * aux_cpu_time;
  }

  // calculate mean and std
  double mean_wall_time = wall_time / nreps;
  double mean_cpu_time = cpu_time / nreps;
  double std_wall_time = std::sqrt((squared_wall_time / nreps - mean_wall_time * mean_wall_time) / nreps);
  double std_cpu_time = std::sqrt((squared_cpu_time / nreps - mean_cpu_time * mean_cpu_time) / nreps);

  // print results
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  std::cout << size << " "
            << mean_wall_time << " " << std_wall_time << " "
            << mean_cpu_time << " " << std_cpu_time << "\n";

}

void matmul_eigen(int size, int nreps) {
  // cummulative time
  double wall_time = 0.0;
  double squared_wall_time = 0.0;
  double cpu_time = 0.0;
  double squared_cpu_time = 0.0;

  for (int ii = 0; ii < nreps; ++ii) {
    // set a new seed
    srand(ii);

    // create matrices
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(size, size);

    // start time measure
    auto start = std::chrono::steady_clock::now(); // wall clock
    std::clock_t c1 = std::clock(); // cpu clock

    // computation
    auto C { A * B }; // multiplication
    double tmp = C(0, 0); // force computation

    // end time measure
    auto end = std::chrono::steady_clock::now(); // wall clock
    std::clock_t c2 = std::clock(); // cpu clock

    std::clog << tmp << std::endl;

    // accumulate measured time
    double aux_cpu_time = 1.0 * (c2 - c1) / CLOCKS_PER_SEC;
    std::chrono::duration<double> elapsed_seconds = end - start;
    double aux_wall_time = elapsed_seconds.count();
    wall_time += aux_wall_time;
    squared_wall_time += aux_wall_time * aux_wall_time;
    cpu_time += aux_cpu_time;
    squared_cpu_time += aux_cpu_time * aux_cpu_time;
  }

  // calculate mean and std
  double mean_wall_time = wall_time / nreps;
  double mean_cpu_time = cpu_time / nreps;
  double std_wall_time = std::sqrt((squared_wall_time / nreps - mean_wall_time * mean_wall_time) / nreps);
  double std_cpu_time = std::sqrt((squared_cpu_time / nreps - mean_cpu_time * mean_cpu_time) / nreps);

  // print results
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  std::cout << size << " "
            << mean_wall_time << " " << std_wall_time << " "
            << mean_cpu_time << " " << std_cpu_time << "\n";
}

// COMPILATION

    // WITHOUT O3
    // g++ -g -std=c++17 -fsanitize=address,undefined matmul.cpp -o matmul

    // WITH O3
    // g++ -g -std=c++17 -O3 -fsanitize=address,undefined matmul.cpp -o matmul_O3

    // WITH O3 AND OPENMP
    // g++ -g -std=c++17 -O3 -fopenmp -fsanitize=address,undefined matmul.cpp -o matmul_O3_OPM

// EXECUTION: We're going to use 30 iterations in each case.

    // STRONG SCALING -- In reality this is weak scaling

        // WITH EIGEN WITHOUT O3
        // for S in 10 50 100 200 500 1000 2000 3000 4000; do ./matmul 1 $S 30 2> /dev/null >> strong_eigen.txt; done
        
        // WITH EIGEN WITH O3
        // for S in 10 50 100 200 500 1000 2000 3000 4000; do ./matmul_O3 1 $S 30 2> /dev/null >> strong_eigen_O3.txt; done

        // WITHOUT EIGEN WITHOUT O3
        // for S in 10 50 100 200 500 1000 2000 3000 4000; do ./matmul 0 $S 30 2> /dev/null >> strong_simple.txt; done
        
        // WITHOUT EIGEN WITH O3
        // for S in 10 50 100 200 500 1000 2000 3000 4000; do ./matmul_O3 0 $S 30 2> /dev/null >> strong_simple_O3.txt; done

    // WEAK SCALING -- In reality this is strong scaling

        // WITH EIGEN WITH 03
        /*
        for th in `seq 16`; do 
            echo "$th" >> weak_eigen_O3_OMP.txt 
            OMP_NUM_THREADS=$th ./matmul_O3_OPM 1 4000 30 2> /dev/null >> weak_eigen_O3_OMP.txt; 
	    done
        */
    
    // strong_eigen_i5 and strong_simple_i5 were generated with only 5 iterations each, but they won't be used for plots