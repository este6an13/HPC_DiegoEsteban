#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
 
int main()
{
    std::vector<double> v(1000); // vector of numbers
    std::random_device rd;  // seed gen
    std::mt19937 gen(rd()); // engine
    
    std::normal_distribution<double> distrib(-10.0, 17.0);
  
    double num;
    for (int i = 0; i < 1000; i++) {
        num = distrib(gen);
        v[i] = num;
        std::cout << num << '\n';
    }

    // all less than 7 check
    bool all_lt7 = std::all_of(v.begin(), v.end(), [](double x){ return x < 7.0; });
    if (all_lt7)
        std::cout << "Todos menores que 7.0\n";

    // any greater than 9 check
    bool any_gt9 = std::any_of(v.begin(), v.end(), [](double x){ return x > 9.0; });
    if (any_gt9)
        std::cout << "Al menos uno mayor que 9.0\n";

    auto it = std::find_if(v.begin(), v.end(), [](double x){ return x > 3.0; });
    if (it != v.end())
        std::cout << "El primer elemento mayor que 3.0 es " << *it << '\n';
}

