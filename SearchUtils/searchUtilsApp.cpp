#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <numeric>
#include "searchUtils.h"

int main() {
    std::vector<int> sizes = {10000,20000,30000,40000,50000,60000,70000,80000,90000,100000};

    // Random generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Prepare output files
    std::ofstream csvLinear("SearchUtils_linear_results.csv");
    std::ofstream csvBinary("SearchUtils_binary_results.csv");

    // Print headers
    std::cout << "LINEAR SEARCH RESULTS:\n";
    std::cout << "Vector_Size,Random1,Random2,Random3,Random4,Random5,Random6,Random7,Average\n";
    csvLinear << "Vector_Size,Random1,Random2,Random3,Random4,Random5,Random6,Random7,Average\n";

    for (int n : sizes) {
        auto arr = generateSortedVector(n);
        std::uniform_int_distribution<> dist(1, n);
        std::vector<int> comps;
        comps.reserve(7);
        for (int i = 0; i < 7; ++i) {
            int key = dist(gen);
            int index = -1;
            int comparisons = linearSearch(arr, key, index);
            comps.push_back(comparisons);
        }
        double avg = std::accumulate(comps.begin(), comps.end(), 0.0) / comps.size();
        // Output
        std::cout << n;
        csvLinear << n;
        for (int c : comps) {
            std::cout << "," << c;
            csvLinear << "," << c;
        }
        std::cout << "," << avg << "\n";
        csvLinear << "," << avg << "\n";
    }

    // Binary search results
    std::cout << "\nBINARY SEARCH RESULTS:\n";
    std::cout << "Vector_Size,Random1,Random2,Random3,Random4,Random5,Random6,Random7,Average\n";
    csvBinary << "Vector_Size,Random1,Random2,Random3,Random4,Random5,Random6,Random7,Average\n";

    for (int n : sizes) {
        auto arr = generateSortedVector(n); // already sorted
        std::uniform_int_distribution<> dist(1, n);
        std::vector<int> comps;
        comps.reserve(7);
        for (int i = 0; i < 7; ++i) {
            int key = dist(gen);
            int index = -1;
            int comparisons = binarySearch(arr, key, index);
            comps.push_back(comparisons);
        }
        double avg = std::accumulate(comps.begin(), comps.end(), 0.0) / comps.size();
        // Output
        std::cout << n;
        csvBinary << n;
        for (int c : comps) {
            std::cout << "," << c;
            csvBinary << "," << c;
        }
        std::cout << "," << avg << "\n";
        csvBinary << "," << avg << "\n";
    }

    csvLinear.close();
    csvBinary.close();
    return 0;
}
