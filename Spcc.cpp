#include "spcc.h"
#include <numeric>
#include <cmath>

/**
 * @brief Calculates the scaled Pearson correlation coefficient (sPCC) between two vectors.
 *
 * The scaled Pearson correlation coefficient is a measure of the linear correlation between
 * two sets of data, scaled to the range [-1, 1].
 *
 * @param x The first vector of data points.
 * @param y The second vector of data points.
 * @return The scaled Pearson correlation coefficient between x and y.
 */
double sPCC(const std::vector<double>& x, const std::vector<double>& y) {
    // Calculate sum of elements in x and y
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);

    // Calculate sum of squares of elements in x and y
    double sum_x2 = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    double sum_y2 = std::inner_product(y.begin(), y.end(), y.begin(), 0.0);

    // Calculate sum of product of corresponding elements in x and y
    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

    size_t n = x.size();
    // Calculate numerator and denominator for sPCC formula
    double numerator = n * sum_xy - sum_x * sum_y;
    double denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

    // Avoid division by zero
    if (denominator == 0) return 0;
    // Calculate and return sPCC
    return numerator / denominator;
}
