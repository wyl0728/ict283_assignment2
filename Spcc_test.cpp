#include "spcc.h"
#include <iostream>
#include <vector>
#include <iomanip>

/**
 * @brief Calculates the sPCC (Smoothed Pearson Correlation Coefficient) between two vectors.
 *
 * @param x The first vector.
 * @param y The second vector.
 * @return The calculated sPCC value.
 */

int main() {
    // Example data vectors
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 5, 4, 5};

    // Additional data sets can be added for more comprehensive testing
    std::vector<double> x2 = {10, 20, 30, 40, 50};
    std::vector<double> y2 = {15, 25, 35, 45, 55};

    // Call the sPCC function with the example data
    double result = sPCC(x, y);
    double result2 = sPCC(x2, y2);

    // Output the result with fixed point notation
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "sPCC for first set of data: " << result << std::endl;
    std::cout << "sPCC for second set of data: " << result2 << std::endl;

    return 0;
}
