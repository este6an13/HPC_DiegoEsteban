// Diego Esteban Quintero Rey
// Samuel Miranda Rocha
// Daniel Felipe Peralta Macca
// Miguel Angel Arbelaez Llano
// Daniel Santiago Cocinero Jimenez

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>


std::mutex mtx;

void square(const int x, int & result);

int main() {
    int accum = 0;
    std::vector<std::thread> ths;
    for (int i = 1; i <= 20; i++) {
        ths.push_back(std::thread(&square, i, std::ref(accum)));
    }

    for (auto & th : ths) {
        th.join();
    }
    std::cout << "accum = " << accum << std::endl;
    return 0;
}

void square(int x, int &result) {
    mtx.lock();
    result += x * x;
    mtx.unlock();
}
