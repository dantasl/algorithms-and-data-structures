import random

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    else:
        # The task asks to choose a random pivot element
        pivot_index = random.randint(0, len(arr) - 1)
        pivot = arr[pivot_index]

        # Partitioning
        less_than_pivot = [x for x in arr if x < pivot]
        equal_to_pivot = [x for x in arr if x == pivot]
        greater_than_pivot = [x for x in arr if x > pivot]

        # Calls quick_sort on the partitions
        return quick_sort(less_than_pivot) + equal_to_pivot + quick_sort(greater_than_pivot)
