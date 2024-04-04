#include "Calculations.h"
#include <cmath>

/**
 * @brief Calculate average vector values.
 * @param values The vector value used to calculate average value.
 * @return Average vector values.
 */
float CalculateAverage(const std::vector<float>& values) {
    if(values.empty()) return 0.0f;

    float sum = 0.0f;
    int count = 0;
    for (float value : values) {
        if (value != -1.0f) { // Assuming -1.0f represents missing values
            sum += value;
            ++count;
        }
    }
    return count > 0 ? sum / count : 0.0f;
}

/**
 * @brief Calculate standard deviation of vector values.
 * @param values The vector values used to calculate standard deviation.
 * @param mean The mean value of the vector.
 * @return The standard deviation of vector values.
 */
float CalculateStandardDeviation(const std::vector<float>& values, float mean) {
    float sum = 0.0f;
    int count = 0;
    for (float value : values) {
        if (value != -1.0f) { // Assuming -1.0f represents missing values
            sum += std::pow(value - mean, 2);
            ++count;
        }
    }
    return count > 1 ? std::sqrt(sum / (count - 1)) : 0.0f;
}
