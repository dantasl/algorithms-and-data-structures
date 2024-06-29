from insertion_sort import insertion_sort
from quick_sort import quick_sort
from merge_sort import merge_sort
import numpy as np
import time
import random

insertion_sort_times, quick_sort_times, merge_sort_times = [], [], []

# Insertion sort
for i in range(50):
    arr = [random.randint(0, 100000) for _ in range(100000)]
    start_time = time.time()
    sorted_arr = insertion_sort(arr)
    end_time = time.time()
    
    content = f"Time taken for insertion sort, { i } iteration: { end_time - start_time } seconds \n"
    with open ('insertion_sort_times.txt', 'a') as file:
        file.write(content)
    
    print(content)
    insertion_sort_times.append(end_time - start_time)

# Merge sort
for i in range(50):
    arr = [random.randint(0, 100000) for _ in range(100000)]
    start_time = time.time()
    sorted_arr = merge_sort(arr)
    end_time = time.time()
    
    content = f"Time taken for merge sort, { i } iteration: { end_time - start_time } seconds \n"
    with open ('merge_sort_times.txt', 'a') as file:
        file.write(content)
    
    print(content)
    merge_sort_times.append(end_time - start_time)

# Quick sort
for i in range(50):
    arr = [random.randint(0, 100000) for _ in range(100000)]
    start_time = time.time()
    sorted_arr = quick_sort(arr)
    end_time = time.time()

    content = f"Time taken for quick sort, { i } iteration: { end_time - start_time } seconds \n"
    with open ('quick_sort_times.txt', 'a') as file:
        file.write(content)

    print(content)
    quick_sort_times.append(end_time - start_time)

# Calculate the average time taken for each algorithm
insertion_sort_average = np.mean(insertion_sort_times)
insertion_sort_std_deviation = np.std(insertion_sort_times)
print("Insertion sort average time: ", insertion_sort_average)
print("Insertion sort standard deviation: ", insertion_sort_std_deviation)

merge_sort_average = np.mean(merge_sort_times)
merge_sort_std_deviation = np.std(merge_sort_times)
print("Merge sort average time: ", merge_sort_average)
print("Merge sort standard deviation: ", merge_sort_std_deviation)

quick_sort_average = np.mean(quick_sort_times)
quick_sort_std_deviation = np.std(quick_sort_times)
print("Quick sort average time: ", quick_sort_average)
print("Quick sort standard deviation: ", quick_sort_std_deviation)
