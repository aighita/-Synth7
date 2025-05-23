// File: Degree.h
#ifndef DEGREE_H
#define DEGREE_H

#include <stdint.h>

// Nashville Scale Degrees
// Represents scale degrees I–VII
enum class Degree : uint8_t {
    I = 0,
    II,
    III,
    IV,
    V,
    VI,
    VII,
    Count
};

#endif // DEGREE_H
