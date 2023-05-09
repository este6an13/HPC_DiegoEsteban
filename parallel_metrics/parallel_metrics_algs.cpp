#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>
#include <omp.h>

template<typename Func>
void time_function(Func func, int T, int P);

int main(int argc, char ** argv)
{
    if (argc != 2) {
        std::cerr << "Error: Usage: \n" << argv[0] << "T P\n";
        std::cerr << "P: Execution Policy\n";
        return 1;
    }
    
    const int T = omp_get_max_threads(); // Number of Threads
    const int P = std::stoi(argv[1]); // Execution Policy

    const long ARRAY_SIZE = 200000000;
    std::vector<double> myArray(ARRAY_SIZE);
    std::iota(myArray.begin(), myArray.end(), 0);

    if (P == 1) {
        auto execution = [&myArray](){return std::reduce(std::execution::seq, myArray.begin(), myArray.end());};
        time_function(execution, T, P);
    }
    else if (P == 2) {
        auto execution = [&myArray](){return std::reduce(std::execution::par, myArray.begin(), myArray.end());};
        time_function(execution, T, P);
    }
    else if (P == 3) {
        auto execution = [&myArray](){return std::reduce(std::execution::par_unseq, myArray.begin(), myArray.end());};
        time_function(execution, T, P);
    }
    else {
        auto execution = [&myArray](){return std::reduce(std::execution::unseq, myArray.begin(), myArray.end());};
        time_function(execution, T, P);        
    }

    return 0;
}

template<typename Func>
void time_function(Func func, int T, int P) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    std::cout << T << " " << P << " " << duration_ms/1000.0 << "\n";
}

// COMPILATION
    // g++ -g -std=c++17 -O3 -fopenmp -fsanitize=address,undefined parallel_metrics_algs.cpp -o main.x

// EXECUTION
    // for t in $(seq 17); do parallel -j 4 "OMP_NUM_THREADS=$t ./main.x {} >/dev/null >> times.txt" ::: $(seq 4); done
