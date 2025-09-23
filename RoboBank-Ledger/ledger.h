/**
 * @file ledger.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ROBOBANK_LEDGER_LEDGER_H_
#define ROBOBANK_LEDGER_LEDGER_H_

#include <stdint.h>

extern std::string rounding;

int32_t Find_account_index(std::string ac_account_id[], int32_t& ac_count, 
    const std::string& account_id);
int32_t Get_or_create_account(std::string ac_account_id[], int64_t* ac_balance, 
    const int32_t& ac_capacity, int32_t& ac_count, const std::string& account_id);
void Apply_one(std::string ac_account_id[], int64_t* ac_balance, const int32_t& ac_capacity, 
    int32_t& ac_count, const std::string& account_id, int32_t& tx_type, int32_t& amount_cents);
void Apply_all(std::string tx_account_id[], int32_t* tx_type, int32_t* tx_amount_cents, 
    const int32_t& tx_count, std::string ac_account_id[], int64_t* ac_balance, 
    const int32_t& ac_capacity, int32_t& ac_count);
int64_t Balance_of(std::string ac_account_id[], int64_t* ac_balance, int32_t& ac_count, 
    const std::string& account_id);
void Bank_summary(int32_t* tx_type, int32_t* tx_amount_cents, const int32_t& tx_count,
    int64_t* ac_balance, const int32_t& ac_count, int64_t& out_total_deposits,
    int64_t& out_total_withdrawals, int64_t& out_total_fees,
    int64_t& out_total_interest, int64_t& out_net_exposure);

#endif  //  ROBOBANK_LEDGER_LEDGER_H_