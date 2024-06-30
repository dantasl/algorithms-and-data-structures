//    Compile: g++ -Wall -std=c++11 merge_sort.cpp -o merge_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>
#include <ctime> // time
#include <cstdlib> // rand, srand
#include <chrono> // chrono::steady_clock
#include <numeric> // accumulate
#include <cmath> // sqrt

bool compare(int a, int b) { return (a < b); }

void merge(std::vector<int> &A, std::vector<int>::iterator begin, std::vector<int>::iterator middle, std::vector<int>::iterator last, bool(*cmp)(int, int))
{
    std::vector<int> left_array;
    std::vector<int> right_array;

    for (auto i = begin; i <= middle; ++i)
        left_array.push_back(*i);
    for (auto j = middle + 1; j <= last; ++j)
        right_array.push_back(*j);

    auto i = left_array.begin();
    auto j = right_array.begin();
    auto to_merge = begin;

    while (i != left_array.end() and j != right_array.end())
    {
        if (cmp(*i, *j))
            std::swap(*to_merge++, *i++);
        else
            std::swap(*to_merge++, *j++);
    }

    while (i != left_array.end())
        *to_merge++ = *i++;
    while (j != right_array.end())
        *to_merge++ = *j++;
}

void merge_sort(std::vector<int> &A, std::vector<int>::iterator begin, std::vector<int>::iterator end, bool(*cmp)(int, int))
{
    if (begin < end)
    {
        auto middle = begin + std::distance(begin, end) / 2;
        merge_sort(A, begin, middle, cmp);
        merge_sort(A, middle + 1, end, cmp);
        merge(A, begin, middle, end, cmp);
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
        merge_sort(arr, arr.begin(), arr.end(), compare);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        executionTimes[i] = elapsed.count();
    }

    double sum = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double mean = sum / numIterations;

    double sq_sum = std::inner_product(executionTimes.begin(), executionTimes.end(), executionTimes.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / numIterations - mean * mean);

    std::cout << "Merge Sort: Average execution time: " << mean << " seconds" << std::endl;
    std::cout << "Merge Sort: Standard deviation: " << stdev << " seconds" << std::endl;

    return 0;
}