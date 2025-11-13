#pragma once
#include <vector>

// --- Linear search ---
// Returns the index of key in arr, or -1 if not found.
// comparisons will contain the number of element comparisons made.
int linearSearch(std::vector<int>& arr, int key, int& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        ++comparisons; // one comparison between arr[i] and key
        if (arr[i] == key) return static_cast<int>(i);
    }
    return -1;
}


// --- Iterative binary search ---
// Returns the index of key in arr, or -1 if not found.
// comparisons will contain the number of element comparisons made.
// arr must be sorted in non-decreasing order.
int binarySearch(const std::vector<int>& arr, int key, int& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        ++comparisons; // compare arr[mid] == key
        if (arr[mid] == key) return mid;
        ++comparisons; // compare arr[mid] < key
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
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
