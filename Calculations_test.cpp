#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "Calculations.h"

// Function prototypes
float CalculateAverage(const std::vector<float>& values);
float CalculateStandardDeviation(const std::vector<float>& values, float mean);

// Helper function to compare floats with a tolerance
bool RoughlyEqual(float a, float b, float epsilon = 0.001) {
    return std::fabs(a - b) < epsilon;
}

// Test function for CalculateAverage
void TestCalculateAverage() {
    std::vector<float> values = {1, 2, 3, 4, 5};
    float average = CalculateAverage(values);
    assert(RoughlyEqual(average, 3.0));
    std::cout << "CalculateAverage test passed!" << std::endl;
}

// Test function for CalculateStandardDeviation
void TestCalculateStandardDeviation() {
    std::vector<float> values = {2, 4, 4, 4, 5, 5, 7, 9};
    float mean = CalculateAverage(values);
    float stdDev = CalculateStandardDeviation(values, mean);
    std::cout << "Calculated StdDev: " << stdDev << std::endl; // Debug output
    assert(RoughlyEqual(stdDev, 2.13809, 0.01));
    std::cout << "CalculateStandardDeviation test passed!" << std::endl;
}


int main() {
    testCalculateAverage();
    testCalculateStandardDeviation();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

