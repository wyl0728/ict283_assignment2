#ifndef SPCC_H
#define SPCC_H

#include <vector>

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
double sPCC(const std::vector<double>& x, const std::vector<double>& y);

#endif
