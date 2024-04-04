#include "Time.h"

/**
 * @brief Constructs a new Time object with the given hour, minute, and second.
 * @param hour The hour of the time.
 * @param minute The minute of the time.
 * @param second The second of the time.
 */
 Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {
}

/**
 * @brief Overloaded stream insertion operator for Time class.
 * @details Inserts the time in the format "hour:minute:second" into output stream.
 * @param os The output stream.
 * @param time The time to be inserted into stream.
 * @return Output.
 */
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << (time.GetHour() < 10 ? "0" : "") << time.GetHour() << ":"
       << (time.GetMinute() < 10 ? "0" : "") << time.GetMinute() << ":"
       << (time.GetSecond() < 10 ? "0" : "") << time.GetSecond();
    return os;
}
