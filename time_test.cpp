#include "Time.h"
#include <iostream>

int main() {
    // Test default constructor
    Time defaultTime;
    std::cout << "Default Time: " << defaultTime << std::endl;

    // Test parameterized constructor
    Time time1(12, 30, 45);
    std::cout << "Time 1: " << time1 << std::endl;

    // Test get methods
    std::cout << "Hour of Time 1: " << time1.getHour() << std::endl;
    std::cout << "Minute of Time 1: " << time1.getMinute() << std::endl;
    std::cout << "Second of Time 1: " << time1.getSecond() << std::endl;

    // Test comparison operators
    Time time2(15, 20, 10);
    Time time3(12, 30, 45);

    std::cout << "Time 1: " << time1 << std::endl;
    std::cout << "Time 2: " << time2 << std::endl;
    std::cout << "Time 3: " << time3 << std::endl;
    std::cout << "Time 1 < Time 2: " << (time1 < time2) << std::endl;
    std::cout << "Time 1 > Time 2: " << (time1 > time2) << std::endl;
    std::cout << "Time 1 == Time 2: " << (time1 == time2) << std::endl;
    std::cout << "Time 1 != Time 2: " << (time1 != time2) << std::endl;

    std::cout << "Time 1 == Time 3: " << (time1 == time3) << std::endl;

    return 0;
}
