#pragma once
#include <vector>

// --- Linear search ---
// Returns the number of comparisons made.
// index will contain the index of key in arr, or -1 if not found.
int linearSearch(const std::vector<int>& arr, int key, int& index) {
    int comparisons = 0;
    index = -1;
    for (size_t i = 0; i < arr.size(); ++i) {
        ++comparisons; // compare arr[i] and key
        if (arr[i] == key) {
            index = static_cast<int>(i);
            return comparisons;
        }
    }
    return comparisons;
}


// --- Iterative binary search ---
// Returns the number of comparisons made.
// index will contain the index of key in arr, or -1 if not found.
// arr must be sorted in non-decreasing order.
int binarySearch(const std::vector<int>& arr, int key, int& index) {
    int comparisons = 0;
    index = -1;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        ++comparisons; // compare arr[mid] == key
        if (arr[mid] == key) {
            index = mid;
            return comparisons;
        }
        ++comparisons; // compare arr[mid] < key
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return comparisons;
}


// --- Generate sorted vector ---
// Returns a vector of n integers sorted in non-decreasing order.
// The numbers are consecutive starting from 1.
std::vector<int> generateSortedVector(int n) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 1; i <= n; ++i) v.push_back(i);
    return v;
}
