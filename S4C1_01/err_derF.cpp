#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;

int main() {

  double PI2 = M_PI / 2.0;
  double h = 0.01;
  double t = -PI2 + h; 
  double D; // approximated derivative
  double d; // analytical derivative
  double e; // error

  // Forward Difference
  while (t < PI2) {
    D = (sin(t + h) - sin(t)) / h;
    d = cos(t);
    e = std::abs((D - d) / d);
    cout << std::scientific << std::setw(20) << std::setprecision(16) << t << "\t" << D << "\t" << d << "\t" << e <<"\n";
    t += h;
  }
    
  return 0;
}
