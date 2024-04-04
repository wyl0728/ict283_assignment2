#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <vector>

/**
 * @brief Calculate average vector values.
 * @param values The vector value used to calculate average value.
 * @return Average vector values.
 */
float CalculateAverage(const std::vector<float>& values);

/**
 * @brief Calculate standard deviation of vector values.
 * @param values The vector values used to calculate standard deviation.
 * @param mean The mean value of the vector.
 * @return The standard deviation of vector values.
 */
float CalculateStandardDeviation(const std::vector<float>& values, float mean);
#endif
