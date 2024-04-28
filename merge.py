# Write a python function for merge/quick sort for integer list as parameter to it.

def merge_sort(arr):
    """
    Sorts an integer list using the Merge Sort algorithm.
    
    Args:
    - arr: The integer list to be sorted.
    
    Returns:
    - The sorted integer list.
    """
    if len(arr) <= 1:
        return arr
    
    # Split the array into two halves
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    # Recursively sort each half
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)
    
    # Merge the sorted halves
    return merge(left_half, right_half)

def merge(left_half, right_half):
    """
    Merges two sorted integer lists into a single sorted list.
    
    Args:
    - left_half: The first sorted integer list.
    - right_half: The second sorted integer list.
    
    Returns:
    - The merged sorted integer list.
    """
    result = []
    left_ptr = right_ptr = 0
    
    # Merge the two lists
    while left_ptr < len(left_half) and right_ptr < len(right_half):
        if left_half[left_ptr] < right_half[right_ptr]:
            result.append(left_half[left_ptr])
            left_ptr += 1
        else:
            result.append(right_half[right_ptr])
            right_ptr += 1
    
    # Add any remaining elements from the left half
    while left_ptr < len(left_half):
        result.append(left_half[left_ptr])
        left_ptr += 1
    
    # Add any remaining elements from the right half
    while right_ptr < len(right_half):
        result.append(right_half[right_ptr])
        right_ptr += 1
    
    return result

def quick_sort(arr):
    """
    Sorts an integer list using the Quick Sort algorithm.
    
    Args:
    - arr: The integer list to be sorted.
    
    Returns:
    - The sorted integer list.
    """
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quick_sort(left) + middle + quick_sort(right)

my_list = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]

# Using Merge Sort
sorted_list_merge = merge_sort(my_list)
print("Sorted list using Merge Sort:", sorted_list_merge)

# Using Quick Sort
sorted_list_quick = quick_sort(my_list)
print("Sorted list using Quick Sort:", sorted_list_quick)
