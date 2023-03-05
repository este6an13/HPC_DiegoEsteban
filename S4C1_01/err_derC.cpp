#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;

int main() {

  double PI2 = M_PI / 2.0;
  double h = 0.01;
  double h2 = h / 2.0;
  double t = -PI2 + h; 
  double D; // approximated derivative
  double d; // analytical derivative
  double e; // error

  // Central Difference
  while (t < PI2) {
    D = (sin(t + h2) - sin(t - h2)) / h;
    d = cos(t);
    e = std::abs((D - d) / d);
    cout << std::scientific << std::setw(20) << std::setprecision(16) << t << "\t" << D << "\t" << d << "\t" << e <<"\n";
    t += h;
  }
    
  return 0;
}