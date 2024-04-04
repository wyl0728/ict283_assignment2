#ifndef DATE_H
#define DATE_H
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Represents a date with day, month, and year components.
 */
class Date {
public:
    /**
     * @brief Default constructor for Date.
     */
    Date() = default;
    /**
     * @brief Parameterized constructor for Date.
     * @param day The day component of the date.
     * @param month The month component of the date.
     * @param year The year component of the date.
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets the name of the month corresponding to the month number.
     * @return The name of the month.
     */
    std::string GetMonthName() const;

    /**
     * @brief Getter for the day component of the date.
     * @return The day component.
     */
    int GetDay() const { return day; }

    /**
     * @brief Getter for the month component of the date.
     * @return The month component.
     */
    int GetMonth() const { return month; }

    /**
     * @brief Getter for the year component of the date.
     * @return The year component.
     */
    int GetYear() const { return year; }

    /**
     * @brief Overloaded less-than operator for Date.
     * Compares Date objects based on year, month, and day.
     * @param other The Date object to compare against.
     * @return True if this object is less than the other object, false otherwise.
     */
    bool operator<(const Date& other) const {
        if (year < other.year) return true;
        if (year > other.year) return false;
        if (month < other.month) return true;
        if (month > other.month) return false;
        return day < other.day;
    }

    /**
     * @brief Overloaded greater-than operator for Date.
     * Compares Date objects based on year, month, and day.
     * @param other The Date object to compare against.
     * @return True if this object is greater than the other object, false otherwise.
     */
    bool operator>(const Date& other) const {
        return other < *this;
    }

    /**
     * @brief Overloaded equality operator for Date.
     * Compares Date objects for equality based on year, month, and day.
     * @param other The Date object to compare against.
     * @return True if this object is equal to the other object, false otherwise.
     */
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    /**
     * @brief Overloaded inequality operator for Date.
     * Compares Date objects for inequality based on year, month, and day.
     * @param other The Date object to compare against.
     * @return True if this object is not equal to the other object, false otherwise.
     */
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

private:
int day; ///< The day component of the date.
    int month; ///< The month component of the date.
    int year; ///< The year component of the date.
};

/**
 * @brief Overloaded stream insertion operator for Date.
 * Inserts Date information into the output stream.
 * @param os The output stream.
 * @param date The Date object to insert into the stream.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);

#endif
