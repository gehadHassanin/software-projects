/**
 * @file calculator.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "calculator.h"

#include <stdint.h>

#include <string>
#include <map>

#include "utils.h"

int64_t ApplyDeposit(int64_t balance, int32_t amount) {
    return balance + amount;
}

int64_t ApplyWithdrawal(int64_t balance, int32_t amount) {
    return balance - amount;
}

int64_t ApplyFee(int64_t balance, int32_t amount) {
    return balance - amount;
}

int64_t SimpleInterest(int32_t base, float apr, uint16_t days, 
   uint16_t day_count_basis, const std::string& rounding) {
    float rate = (apr * (static_cast<float>(days))) / day_count_basis;
    return Percent_of(base, rate, rounding);
}

int64_t CompoundAmount(int32_t principal, float apr, uint16_t years, 
   uint16_t  compounds_per_year, const std::string& rounding) {
    float rate = std::pow((1 + (apr / compounds_per_year)),
    (years * compounds_per_year));
    return Percent_of(principal, rate, rounding);
}

int64_t FxConvert(int64_t amount, const std::string& from_currency, 
   const std::string& to_currency, const std::string& rounding) {
    auto it_of_from_currency = fx_table.find(from_currency);
    auto it_of_to_currency = fx_table.find(to_currency);
    if (it_of_from_currency != fx_table.end() && 
        it_of_to_currency != fx_table.end()) {
            float usd_amount = amount * fx_table[from_currency];
            return Percent_of(usd_amount, fx_table[to_currency], rounding); 
    } else {
        return -1;
    }
}