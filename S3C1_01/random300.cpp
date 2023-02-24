#include <cstdlib>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

int min(int *array, int size)
{
    int min = (int) std::numeric_limits<double>::infinity();
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
    }
    return min;
}

int *printOdd(int *array, int size, int limit)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] % 2 != 0)
        {
            cout << array[i] << " ";
        }
        // last number greater than limit is printed if it's odd in this implementation
        if (array[i] > limit)
        {
            break;
        }
    }
    cout << "\n";

    return array;
}
 
int main()
{
    int N = 901;
    int n = 300;
    int array [n];
    
    // to not generate the same sequence each time (default seed is 1)
    srand(time(NULL)); // Initialize the seed with the current time

    // 1. print n random numbers between 0 and N-1
    cout << n << " random numbers between 0 and " << N-1 << ":\n";
    for (int i = 0; i < n; i++) 
    {   int r = rand() % N;
        array[i] = r;
        cout << r << " ";
    }
    cout << "\n\n";

    // 2. get min of array
    cout << "Minimum: " << min(array, n) << "\n\n";

    // 3. print odd up to limit=800
    cout << "Odd numbers up to limit=" << 800 << ":\n\n";
    printOdd(array, n, 800);

    return 0;
}
 
