#include "WeatherData.h"

/**
 * @brief Default constructor for WeatherData.
 * Initializes date, time, temperature, wind speed, and solar radiation to default values.
 */
WeatherData::WeatherData()
    : date(), time(), temperature(0.0f), windSpeed(0.0f), solarRadiation(0.0f) {}

/**
 * @brief Parameterized constructor for WeatherData.
 * @param d Date for the weather data.
 * @param t Time for the weather data.
 * @param temp Temperature for the weather data.
 * @param wind Wind speed for the weather data.
 * @param solar Solar radiation for the weather data.
 */
WeatherData::WeatherData(Date d, Time t, float temp, float wind, float solar)
    : date(d), time(t), temperature(temp), windSpeed(wind), solarRadiation(solar) {}

/**
 * @brief Overloaded less-than operator for WeatherData.
 * Compares WeatherData objects based on date and time.
 * @param other The WeatherData object to compare against.
 * @return True if this object is less than the other object, false otherwise.
 */
bool WeatherData::operator<(const WeatherData& other) const {
    if (date < other.date) return true;
    if (date > other.date) return false;
    return time < other.time;
}

/**
 * @brief Overloaded greater-than operator for WeatherData.
 * Compares WeatherData objects based on date and time.
 * @param other The WeatherData object to compare against.
 * @return True if this object is greater than the other object, false otherwise.
 */
bool WeatherData::operator>(const WeatherData& other) const {
    if (date > other.date) return true;
    if (date < other.date) return false;
    return time > other.time;
}

/**
 * @brief Overloaded equality operator for WeatherData.
 * Compares WeatherData objects for equality based on date and time.
 * @param other The WeatherData object to compare against.
 * @return True if this object is equal to the other object, false otherwise.
 */
bool WeatherData::operator==(const WeatherData& other) const {
    return date == other.date && time == other.time;
}

/**
 * @brief Overloaded stream insertion operator for WeatherData.
 * Inserts WeatherData information into the output stream.
 * @param os The output stream.
 * @param data The WeatherData object to insert into the stream.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const WeatherData& data) {
    os << "Date: " << data.date << ", Time: " << data.time
       << ", Temperature: " << data.temperature
       << "°C, Wind Speed: " << data.windSpeed << "m/s"
       << ", Solar Radiation: " << data.solarRadiation << "W/m^2";
    return os;
}
