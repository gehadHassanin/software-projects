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

#ifndef ROBOBANK_CALCULATOR_CALCULATOR_H_
#define ROBOBANK_CALCULATOR_CALCULATOR_H_

#include <stdint.h>
#include <string>
#include <map>

int64_t Apply_deposit(int64_t balance, int32_t amount);
int64_t Apply_withdrawal(int64_t balance, int32_t amount);
int64_t Apply_fee(int64_t balance, int32_t amount);
int64_t Simple_interest(int32_t base, float apr, uint16_t days, 
   uint16_t day_count_basis, const std::string& rounding);
int64_t Compound_amount(int32_t principal, float apr, uint16_t years, 
   uint16_t  compounds_per_year, const std::string& rounding);
int64_t Fx_convert(int64_t amount, const std::string& from_currency, 
   const std::string& to_currency, const std::string& rounding);

#endif //  ROBOBANK_CALCULATOR_CALCULATOR_H_


