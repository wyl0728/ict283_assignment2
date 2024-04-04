#ifndef WINDRECTYPE_H
#define WINDRECTYPE_H

#include "Date.h"
#include "Time.h"

/**
 * @struct WindRecType
 * @brief Represent wind record with date, time, and speed.
 */
struct WindRecType {
    Date d;         /**< Date of wind record. */
    Time t;         /**< Time of wind record. */
    float speed;    /**< Speed of wind record. */
};

#endif
