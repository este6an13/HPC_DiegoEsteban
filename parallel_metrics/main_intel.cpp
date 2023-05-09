#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>
#include <tbb/task_scheduler_init.h>

template<typename Func>
void time_function(Func func, int T, int P);

int main(int argc, char ** argv)
{
    if (argc != 3) {
        std::cerr << "Error: Usage: \n" << argv[0] << "T P\n";
        std::cerr << "T: Number of Threads\n";
        std::cerr << "P: Execution Policy\n";
        return 1;
    }
    
    const int T = std::stoi(argv[1]); // Number of Threads
    const int P = std::stoi(argv[2]); // Execution Policy

    const long ARRAY_SIZE = 10000;
    std::vector<double> myArray(ARRAY_SIZE);
    std::iota(myArray.begin(), myArray.end(), 0);

    tbb::task_scheduler_init init(T);

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

// g++ -g -std=c++17 -O3 -fsanitize=address,undefined,thread main.cpp -o main.x
// parallel '/main.x {} {} >/dev/null >> times.txt' ::: $(seq 16) ::: $(seq 4)