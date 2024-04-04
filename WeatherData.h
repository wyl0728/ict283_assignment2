#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include "Date.h"
#include "Time.h"
#include <iostream>

/**
 * @brief Represents weather data with date, time, temperature, wind speed, and solar radiation.
 */
struct WeatherData {
    Date date; ///< The date of the weather data.
    Time time; ///< The time of the weather data.
    float temperature; ///< The temperature recorded.
    float windSpeed; ///< The wind speed recorded.
    float solarRadiation; ///< The solar radiation recorded.

    /**
     * @brief Default constructor for WeatherData.
     * Initializes all data members to default values.
     */
    WeatherData();

    /**
     * @brief Parameterized constructor for WeatherData.
     * @param d The date of the weather data.
     * @param t The time of the weather data.
     * @param temp The temperature recorded.
     * @param wind The wind speed recorded.
     * @param solar The solar radiation recorded.
     */
    WeatherData(Date d, Time t, float temp, float wind, float solar);

    /**
     * @brief Overloaded less-than operator for WeatherData.
     * Compares WeatherData objects based on date and time.
     * @param other The WeatherData object to compare against.
     * @return True if this object is less than the other object, false otherwise.
     */
    bool operator<(const WeatherData& other) const;

    /**
     * @brief Overloaded greater-than operator for WeatherData.
     * Compares WeatherData objects based on date and time.
     * @param other The WeatherData object to compare against.
     * @return True if this object is greater than the other object, false otherwise.
     */
    bool operator>(const WeatherData& other) const;

    /**
     * @brief Overloaded equality operator for WeatherData.
     * Compares WeatherData objects for equality based on date, time, temperature, wind speed, and solar radiation.
     * @param other The WeatherData object to compare against.
     * @return True if this object is equal to the other object, false otherwise.
     */
    bool operator==(const WeatherData& other) const;
};

/**
 * @brief Represents aggregated weather data with total wind speed, total solar radiation, and total temperature.
 */
struct AggregatedWeatherData {
    float totalWindSpeed = 0; ///< Total wind speed.
    int windSpeedCount = 0; ///< Count of wind speed records.
    float totalSolarRadiation = 0; ///< Total solar radiation.
    int solarRadiationCount = 0; ///< Count of solar radiation records.
    float totalTemperature = 0; ///< Total temperature.
    int temperatureCount = 0; ///< Count of temperature records.
};

/**
 * @brief Overloaded stream insertion operator for WeatherData.
 * Inserts WeatherData information into the output stream.
 * @param os The output stream.
 * @param data The WeatherData object to insert into the stream.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const WeatherData& data);

#endif
