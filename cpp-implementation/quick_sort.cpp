//    Compile: g++ -Wall -std=c++11 quick_sort.cpp -o quick_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time
#include <vector>  // std::vector
#include <chrono> // chrono::steady_clock
#include <numeric> // accumulate
#include <cmath> // sqrt

bool compare(int a, int b) { return (a < b); }

int* partition(int* _begin, int* _last, bool(*cmp)(int, int))
{
    // Choose a random pivot and swap with the last element
    int pivotIndex = std::rand() % (_last - _begin);
    std::swap(_begin[pivotIndex], *(_last - 1));
    
    int* pivot = _last - 1; // pivot is now the last element
    int* fast = _begin;
    int* slow = _begin; // delimites a range of elements lesser than the pivot

    for (; fast != _last; ++fast) // iterates over each element of the array
    {
        if (cmp(*fast, *pivot)) // if element is lesser than pivot
        {
            std::swap(*slow, *fast); // place that element on the left end of pivot
            slow++;
        }
    }
    std::swap(*slow, *pivot); // place pivot after its immediate lesser value.
    return slow; // returns address of the pivot
}

void quick_sort(int* _begin, int* _last, bool(*cmp)(int, int))
{
    if (_begin < _last - 1)
    {
        int* partitioned = partition(_begin, _last, cmp);
        quick_sort(_begin, partitioned, cmp); // apply recursion on left elements of pivot
        quick_sort(partitioned + 1, _last, cmp); // apply recursion on right elements of pivot        
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
        quick_sort(arr.data(), arr.data() + arraySize, compare);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Quick Sort #" << i << " iteration, execution time: " << std::chrono::duration<double>(elapsed).count() << " seconds" << std::endl;
        executionTimes[i] = elapsed.count();
    }

    double sum = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double mean = sum / numIterations;

    double sq_sum = std::inner_product(executionTimes.begin(), executionTimes.end(), executionTimes.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / numIterations - mean * mean);

    std::cout << "Quick Sort: Average execution time: " << mean << " seconds" << std::endl;
    std::cout << "Quick Sort: Standard deviation: " << stdev << " seconds" << std::endl;

    return 0;
}