// Diego Esteban Quintero Rey
// Cesar Esteban Diaz Medina
// Diego Fernando Mejia Hernandez

#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
  std::cout << "BEFORE\n";
#pragma omp parallel
  {
    printf("Hola mundo %d\n", omp_get_thread_num());
  }
  std::cout << "AFTER\n";
    
  return 0;
}

