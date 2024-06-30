//    Compile: g++ -Wall -std=c++11 insertion_sort.cpp -o insertion_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>
#include <ctime> // time
#include <cstdlib> // rand, srand
#include <chrono> // chrono::steady_clock
#include <numeric> // accumulate
#include <cmath> // sqrt

bool compare( int a, int b ){ return ( a < b ); }

void insertion_sort(int* _begin, int* _last, bool(*cmp)(int, int))
{
    int* it = _begin; // points to the beginning of the range
    for (; it != _last; ++it) // iterates over each member to sort
    {
        int* carry = it; // unsorted number of the round
        while (carry != _begin && cmp(*carry, *(carry - 1))) // decrements from "it" till beginning of the range
        {
            std::swap(*carry, *(carry - 1));
            carry--;
        }
    }
}

int main()
{
    std::srand(std::time(nullptr)); // initialize random seed

    const int numIterations = 50;
    const int arraySize = 100000;
    std::vector<double> executionTimes(numIterations);

    for (int i = 0; i < numIterations; ++i)
    {
        std::vector<int> arr(arraySize);
        for (int& num : arr) num = std::rand();

        auto start = std::chrono::steady_clock::now();
        insertion_sort(arr.data(), arr.data() + arraySize, compare);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        executionTimes[i] = elapsed.count();
    }

    double sum = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double mean = sum / numIterations;

    double sq_sum = std::inner_product(executionTimes.begin(), executionTimes.end(), executionTimes.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / numIterations - mean * mean);

    std::cout << "Insertion Sort: Average execution time: " << mean << " seconds" << std::endl;
    std::cout << "Insertion Sort: Standard deviation: " << stdev << " seconds" << std::endl;

    return 0;
}