#include "Date.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Constructs a new Date object with the given day, month, and year.
 * @param day The day of the date.
 * @param month The month of the date.
 * @param year The year of the date.
 */
Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

/**
 * @brief Gets the name of the month corresponding to the month number.
 * @return The name of the month or "Invalid month" if the month number is invalid.
 */
std::string Date::GetMonthName() const {
    static const std::vector<std::string> MonthNames = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    if (month >= 1 && month <= 12) {
        return MonthNames[month - 1];
    } else {
        return "Invalid month";
    }
}

/**
 * @brief Overloaded stream insertion operator to print a Date object in the format "DD/MM/YYYY".
 * @param os The output stream.
 * @param date The Date object to be printed.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setw(2) << std::setfill('0') << date.GetDay() << '/'
       << std::setw(2) << std::setfill('0') << date.GetMonth() << '/'
       << date.GetYear();
    return os;
}
