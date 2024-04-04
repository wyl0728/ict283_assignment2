#include "Date.h"
#include "Time.h"
#include "WindRecType.h"
#include "Bst.h"
#include "WeatherData.h"
#include <iostream>

int main() {
    // Test Date class
    Date date1(10, 3, 2022);
    std::cout << "Date 1: " << date1 << std::endl;

    Date date2(15, 3, 2022);
    std::cout << "Date 2: " << date2 << std::endl;

    std::cout << "Date 1 < Date 2: " << (date1 < date2) << std::endl;
    std::cout << "Date 1 > Date 2: " << (date1 > date2) << std::endl;
    std::cout << "Date 1 == Date 2: " << (date1 == date2) << std::endl;

    // Test Time class
    Time time1(12, 30, 0);
    std::cout << "Time 1: " << time1 << std::endl;

    Time time2(14, 45, 0);
    std::cout << "Time 2: " << time2 << std::endl;

    std::cout << "Time 1 < Time 2: " << (time1 < time2) << std::endl;
    std::cout << "Time 1 > Time 2: " << (time1 > time2) << std::endl;
    std::cout << "Time 1 == Time 2: " << (time1 == time2) << std::endl;

    // Test WindRecType struct
    WindRecType windRecord1{date1, time1, 15.5f};
    WindRecType windRecord2{date2, time2, 20.2f};

    std::cout << "Wind Record 1 Date: " << windRecord1.d << ", Time: " << windRecord1.t
              << ", Speed: " << windRecord1.speed << std::endl;

    std::cout << "Wind Record 2 Date: " << windRecord2.d << ", Time: " << windRecord2.t
              << ", Speed: " << windRecord2.speed << std::endl;

    std::cout << "Wind Record 1 < Wind Record 2: " << (windRecord1.d < windRecord2.d) << std::endl;
    std::cout << "Wind Record 1 > Wind Record 2: " << (windRecord1.d > windRecord2.d) << std::endl;
    std::cout << "Wind Record 1 == Wind Record 2: " << (windRecord1.d == windRecord2.d) << std::endl;

    // Test Bst with WeatherData
    Bst<WeatherData> WeatherBst;

    WeatherData data1(Date(10, 3, 2022), Time(12, 30, 0), 25.5f, 12.5f, 1000.0f);
    WeatherData data2(Date(15, 3, 2022), Time(14, 45, 0), 20.0f, 15.0f, 1200.0f);
    WeatherData data3(Date(20, 3, 2022), Time(10, 15, 0), 30.0f, 10.0f, 800.0f);

    WeatherBst.insert(data1);
    WeatherBst.insert(data2);
    WeatherBst.insert(data3);

    std::cout << "In-order traversal of WeatherData BST:" << std::endl;
    WeatherBst.InOrderTraversal([](const WeatherData& data) {
        std::cout << data << std::endl;
    });

    return 0;
}
