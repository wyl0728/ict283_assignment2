#include "Date.h"
#include <iostream>

int main() {
    // Test default constructor
    Date defaultDate;
    std::cout << "Default Date: " << defaultDate << std::endl;

    // Test parameterized constructor
    Date date1(10, 3, 2022);
    std::cout << "Date 1: " << date1 << std::endl;

    // Test get methods
    std::cout << "Day of Date 1: " << date1.getDay() << std::endl;
    std::cout << "Month of Date 1: " << date1.getMonth() << std::endl;
    std::cout << "Year of Date 1: " << date1.getYear() << std::endl;

    // Test getMonthName method
    std::cout << "Month Name of Date 1: " << date1.getMonthName() << std::endl;

    // Test comparison operators
    Date date2(20, 3, 2022);
    Date date3(10, 4, 2022);

    std::cout << "Date 1: " << date1 << std::endl;
    std::cout << "Date 2: " << date2 << std::endl;
    std::cout << "Date 3: " << date3 << std::endl;
    std::cout << "Date 1 < Date 2: " << (date1 < date2) << std::endl;
    std::cout << "Date 1 > Date 2: " << (date1 > date2) << std::endl;
    std::cout << "Date 1 == Date 2: " << (date1 == date2) << std::endl;
    std::cout << "Date 1 != Date 2: " << (date1 != date2) << std::endl;

    std::cout << "Date 1 < Date 3: " << (date1 < date3) << std::endl;
    std::cout << "Date 1 > Date 3: " << (date1 > date3) << std::endl;
    std::cout << "Date 1 == Date 3: " << (date1 == date3) << std::endl;
    std::cout << "Date 1 != Date 3: " << (date1 != date3) << std::endl;

    return 0;
}
