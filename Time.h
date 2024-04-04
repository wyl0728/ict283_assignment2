#ifndef TIME_H
#define TIME_H
#include <iostream>

/**
 * @brief Represents a time with hour, minute, and second components.
 */
class Time {
public:
    /**
     * @brief Default constructor for Time.
     */
    Time() = default;

    /**
     * @brief Parameterized constructor for Time.
     * @param hour The hour component of the time.
     * @param minute The minute component of the time.
     * @param second The second component of the time.
     */
    Time(int hour, int minute, int second);

    /**
     * @brief Getter for the hour component of the time.
     * @return The hour component.
     */
    int GetHour() const { return hour; }
    /**
     * @brief Getter for the minute component of the time.
     * @return The minute component.
     */
    int GetMinute() const { return minute; }

    /**
     * @brief Getter for the second component of the time.
     * @return The second component.
     */
    int GetSecond() const { return second; }

    /**
     * @brief Overloaded less-than operator for Time.
     * Compares Time objects based on hour, minute, and second.
     * @param other The Time object to compare against.
     * @return True if this object is less than the other object, false otherwise.
     */
    bool operator<(const Time& other) const {
        if (hour < other.hour) return true;
        if (hour > other.hour) return false;
        if (minute < other.minute) return true;
        if (minute > other.minute) return false;
        return second < other.second;
    }

    /**
     * @brief Overloaded greater-than operator for Time.
     * Compares Time objects based on hour, minute, and second.
     * @param other The Time object to compare against.
     * @return True if this object is greater than the other object, false otherwise.
     */
    bool operator>(const Time& other) const {
        return other < *this;
    }

    /**
     * @brief Overloaded equality operator for Time.
     * Compares Time objects for equality based on hour, minute, and second.
     * @param other The Time object to compare against.
     * @return True if this object is equal to the other object, false otherwise.
     */
    bool operator==(const Time& other) const {
        return hour == other.hour && minute == other.minute && second == other.second;
    }

    /**
     * @brief Overloaded inequality operator for Time.
     * Compares Time objects for inequality based on hour, minute, and second.
     * @param other The Time object to compare against.
     * @return True if this object is not equal to the other object, false otherwise.
     */
    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

private:
    int hour; ///< The hour component of the time.
    int minute; ///< The minute component of the time.
    int second; ///< The second component of the time.
};

/**
 * @brief Overloaded stream insertion operator for Time.
 * Inserts Time information into the output stream.
 * @param os The output stream.
 * @param time The Time object to insert into the stream.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Time& time);

#endif
