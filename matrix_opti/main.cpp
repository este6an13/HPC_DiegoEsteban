#include <iostream>
#include <eigen3/Eigen/Dense>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>


void solvesystem(int size);

int main(int argc, char ** argv)
{
  // read params
  if (argc != 3) {
    std::cerr << "Error. Usage: \n" << argv[0] << " M S\n";
    std::cerr << "M: Matrix size\n";
    std::cerr << "S: Random generator seed\n";
    return 1;
  }
  const int M = std::stoi(argv[1]); // Matrix size
  const int S = std::stoi(argv[2]); // Matrix size

  // set seed
  srand(S);

  // solve system
  solvesystem(M);

  return 0;
}

void solvesystem(int size)
{


  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd b = Eigen::MatrixXd::Random(size, 1);
  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();
  //Eigen::MatrixXd x = A.fullPivLu().solve(b);
  Eigen::MatrixXd x = A.lu().solve(b);
  // crono end
  // print some results to use the expression and force computation
  std::clock_t c_end = std::clock();
  auto t_end = std::chrono::high_resolution_clock::now();
  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n";
  std::cout << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";
  std::clog << x(0) << std::endl;
}

// usar chrono para medir el tiempo
// gprof
// remove printing
// modify testing
