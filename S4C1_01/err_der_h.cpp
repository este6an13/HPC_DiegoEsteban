#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;

int main() {

  double PI3 = M_PI / 3.0;
  double h = 0.01;
  double h2 = h / 2.0;
  double D; // approximated derivative
  double d; // analytical derivative
  double e; // error
  int ctr = 0;
  
  // Central Difference
  while (ctr < 20) {
   
    D = (sin(PI3 + h2) - sin(PI3 - h2)) / h;
    d = cos(PI3);
    e = std::abs((D - d) / d);
    cout << std::scientific << std::setw(20) << std::setprecision(16) << h << "\t" << D << "\t" << d << "\t" << e <<"\n";   
    
    ctr++;
    h /= 10;
    h2 = h / 2.0;
  }
    
  return 0;
}