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

#ifndef ROBOBANK_PORTFOLIO_INC_UTILS_H_
#define ROBOBANK_PORTFOLIO_INC_UTILS_H_

#include <stdint.h>

#include <cmath>
#include <iostream>
#include <string>
#include <map>

/**
 * @brief Foreign exchange rate lookup table.
 *
 * @details Maps currency codes to their relative rates against a base currency (USD
 *          = 1.0). Example:
 *            - "USD" → 1.0
 *            - "EUR" → 0.91
 */
std::map<std::string, float> fx_table = {{"USD", 1.0}, {"EUR", 0.91}};

/**
 * @brief Calculate a percentage portion of an amount, with rounding options.
 *
 * @param amount The original amount.
 * @param rate The percentage rate (as a decimal, e.g., 0.25 for 25%).
 * @param rounding Rounding mode:
 *   - "HalfUp" → Round to nearest integer, ties away from zero.
 *   - "HalfEven" → Round to nearest even integer (banker's rounding).
 * @return The portion of the amount after applying the rate and rounding,
 *         or -1 if an invalid rounding mode is provided.
 */

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

/**
 * @brief Checks whether a given amount is non-negative.
 *
 * @param amount The value to validate.
 * @return true if the amount is >= 0, false otherwise.
 *
 * @note This is a simple guard utility for input validation,
 *       useful before applying financial operations.
 */
bool Validate_non_negative(int64_t amount) { return amount >= 0; }

#endif  //  ROBOBANK_PORTFOLIO_INC_UTILS_H_
