#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
using namespace std;

int main() {

    vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000};

    for (int s = 0; s < sizes.size(); s++) {
        
        int n = sizes[s];

        // SCENARIO 1: 2D ROWS FIRST
        vector<vector<int>> arr2d(n, vector<int>(n));

        auto start = chrono::steady_clock::now();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr2d[i][j] = 0;
            }
        }

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_time = end - start;
        double duration = elapsed_time.count();
        cout << n * n << " " << 1 << " " << fixed << setprecision(9) << duration << endl;

        vector<int> arr1d(n * n);

        // SCENARIO 2: 1D ROWS FIRST
        start = chrono::steady_clock::now();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr1d[(i * n) + j] = 0;
            }
        }

        end = chrono::steady_clock::now();
        elapsed_time = end - start;
        duration = elapsed_time.count();
        cout << n * n << " " << 2 << " " << fixed << setprecision(9) << duration << endl;

        // SCENARIO 3: 1D COLUMNS FIRST
        start = chrono::steady_clock::now();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr1d[(j * n) + i] = 0;
            }
        }

        end = chrono::steady_clock::now();
        elapsed_time = end - start;
        duration = elapsed_time.count();
        cout << n * n << " " << 3 << " " << fixed << setprecision(9) << duration << endl;

        // SCENARIO 4: 1D SEQUENTIAL
        start = chrono::steady_clock::now();

        for (int i = 0; i < n * n; i++) {
            arr1d[i] = 0;
        }

        end = chrono::steady_clock::now();
        elapsed_time = end - start;
        duration = elapsed_time.count();
        cout << n * n << " " << 4 << " " << fixed << setprecision(9) << duration << endl;


        // SCENARIO 5: 2D COLS FIRST

        start = chrono::steady_clock::now();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr2d[j][i] = 0;
            }
        }

        end = chrono::steady_clock::now();
        elapsed_time = end - start;
        duration = elapsed_time.count();
        cout << n * n << " " << 5 << " " << fixed << setprecision(9) << duration << endl;

    }

    return 0;
}
