def merge_sort(arr):
    if len(arr) > 1:
        # The algorithm starts by getting the middle part of the array
        middle = len(arr) // 2

        # Now, splitting it into two parts
        left_half = arr[:middle]
        right_half = arr[middle:]

        # Call merge_sort() for each half
        merge_sort(left_half)
        merge_sort(right_half)

        i = j = k = 0

        # Start the merge process
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        # Checking if any element was not included
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

    return arr