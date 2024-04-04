#include "WeatherData.h"
#include <iostream>

int main() {
    // Test default constructor
    WeatherData defaultData;
    std::cout << "Default Weather Data: " << defaultData << std::endl;

    // Test parameterized constructor
    Date date(15, 6, 2022);
    Time time(14, 30, 0);
    WeatherData data1(date, time, 25.5f, 10.2f, 500.0f);
    std::cout << "Weather Data 1: " << data1 << std::endl;

    // Test comparison operators
    WeatherData data2(date, time, 22.0f, 9.5f, 480.0f);
    WeatherData data3(date, time, 25.5f, 10.2f, 500.0f);

    std::cout << "Weather Data 1: " << data1 << std::endl;
    std::cout << "Weather Data 2: " << data2 << std::endl;
    std::cout << "Weather Data 3: " << data3 << std::endl;
    std::cout << "Weather Data 1 < Weather Data 2: " << (data1 < data2) << std::endl;
    std::cout << "Weather Data 1 > Weather Data 2: " << (data1 > data2) << std::endl;
    std::cout << "Weather Data 1 == Weather Data 2: " << (data1 == data2) << std::endl;
    std::cout << "Weather Data 1 == Weather Data 3: " << (data1 == data3) << std::endl;

    return 0;
}
