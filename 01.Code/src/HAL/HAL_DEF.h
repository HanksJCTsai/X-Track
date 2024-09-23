#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <stdint.h>

namespace HAL {
    /* Clock */
    typedef struct {
            uint16_t year;
            uint8_t month;
            uint8_t day;
            uint8_t week;
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
            uint16_t millisecond;
    } CLOCK_INFO_T;

    /* IMU */
    typedef struct {
            float ax;
            float ay;
            float az;
            float gx;
            float gy;
            float gz;
            float mx;
            float my;
            float mz;
            float roll;
            float yaw;
            float pitch;
    } IMU_INFO_T;

    /* Power */
    typedef struct {
            uint16_t voltage;
            uint8_t usage;
            bool isCharging;
    } POWER_INFO_T;
} // namespace HAL

#endif