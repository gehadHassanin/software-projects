/**
 * @file utils.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ROBOBANK_CALCULATOR_UTILS_H_
#define ROBOBANK_CALCULATOR_UTILS_H_

#include <iostream>
#include <string>
#include <stdint.h>
#include <cmath>

std::map<std::string, float> fx_table = {{"USD", 1.0}, { "EUR",  0.91}}; 

int64_t Percent_of(int64_t amount, float rate, std::string rounding) {
    double portion = amount * rate;
    if (rounding == "HalfUp") {
        return std::llround(portion);
    } else if (rounding == "HalfEven") {
        return std::nearbyint(portion);
    } else {
        return -1;
    }
}

bool  Validate_rate(float rate) {
    if (rate >= 0 && rate <= 1) {
        return true;
    }
    return false;
}

bool Validate_non_negative(int64_t amount) {
    if (amount >= 0) {
        return true;
    }
    return false;
}

#endif  //  ROBOBANK_CALCULATOR_UTILS_H_