/**
 * @file calculator.h
 * @author
 * @brief
 * @version 0.1
 * @date 2025-09-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ROBOBANK_PORTFOLIO_INC_CALCULATOR_H_
#define ROBOBANK_PORTFOLIO_INC_CALCULATOR_H_

#include <stdint.h>

#include <map>
#include <string>

/**
 * @brief Apply a deposit transaction to a balance.
 * @param balance The current account balance.
 * @param amount The deposit amount.
 * @return The updated balance after applying the deposit.
 */
int64_t ApplyDeposit(int64_t balance, int32_t amount);

/**
 * @brief Apply a withdrawal transaction to a balance.
 * @param balance The current account balance.
 * @param amount The withdrawal amount.
 * @return The updated balance after applying the withdrawal.
 */
int64_t ApplyWithdrawal(int64_t balance, int32_t amount);

/**
 * @brief Apply a fee transaction to a balance.
 * @param balance The current account balance.
 * @param amount The fee amount.
 * @return The updated balance after deducting the fee.
 */
int64_t ApplyFee(int64_t balance, int32_t amount);

/**
 * @brief Calculate the simple interest on a principal amount.
 *
 * Formula: Interest = base × (APR × days / day_count_basis).
 *
 * @param base The principal amount.
 * @param apr The annual percentage rate (as a decimal, e.g., 0.05 for 5%).
 * @param days The number of days interest is applied for.
 * @param day_count_basis The day count convention (e.g., 360 or 365).
 * @param rounding Rounding mode ("up", "down", "nearest").
 * @return The interest amount as an integer (after rounding).
 */
int64_t SimpleInterest(int32_t base, float apr, uint16_t days,
                       uint16_t day_count_basis, const std::string &rounding);

/**
 * @brief Calculate the compound amount after a given number of years.
 *
 * Formula: A = P × (1 + apr / compounds_per_year)^(years × compounds_per_year).
 *
 * @param principal The initial principal amount.
 * @param apr The annual percentage rate (as a decimal).
 * @param years The number of years.
 * @param compounds_per_year The number of compounding periods per year.
 * @param rounding Rounding mode ("up", "down", "nearest").
 * @return The final compounded amount (after rounding).
 */
int64_t CompoundAmount(int32_t principal, float apr, uint16_t years,
                       uint16_t compounds_per_year,
                       const std::string &rounding);

/**
 * @brief Convert an amount between currencies using a foreign exchange rate.
 *
 * The FX rate is assumed to be retrieved internally or configured externally.
 *
 * @param amount The amount to convert.
 * @param from_currency The source currency code (e.g., "USD").
 * @param to_currency The target currency code (e.g., "EUR").
 * @param rounding Rounding mode ("up", "down", "nearest").
 * @return The converted amount in the target currency.
 */
int64_t FxConvert(int64_t amount, const std::string &from_currency,
                  const std::string &to_currency, const std::string &rounding);

#endif  //  ROBOBANK_PORTFOLIO_INC_CALCULATOR_H_

