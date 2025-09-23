/**
 * @file ledger.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <cstring>
#include <memory>

#include "calculator.h"
#include "ledger.h"



extern float apr;
extern uint16_t days;
extern uint16_t years;
extern std::string interest_type;
extern uint16_t day_count_basis;
extern uint16_t  compounds_per_year;

int32_t Find_account_index(std::string ac_account_id[], int32_t& ac_count, 
    const std::string& account_id) {
        for (int32_t iter = 0; iter < ac_count; iter++) {
            if (ac_account_id[iter] == account_id) {
                return iter;
            }
        }
        return -1;
}

int32_t Get_or_create_account(std::string ac_account_id[], int64_t* ac_balance, 
    const int32_t& ac_capacity, int32_t& ac_count, const std::string& account_id) {
        int32_t account_index = Find_account_index(ac_account_id, ac_count, account_id);
        if (account_index != -1) {
            return account_index;
        } else if (ac_count >= ac_capacity) {
            return -1;
        } else {
            ac_account_id[ac_count] = account_id;
            ac_balance[ac_count++] = 0;
            return (ac_count - 1);
        }
}

void Apply_one(std::string ac_account_id[], int64_t* ac_balance, const int32_t& ac_capacity, 
    int32_t& ac_count, const std::string& account_id, int32_t& tx_type, int32_t& amount_cents) {
        int32_t account_index = Get_or_create_account(ac_account_id, ac_balance, 
            ac_capacity, ac_count, account_id);
        if (account_index == -1) {
            // DO NOTHING SPACE IS FULL
        } else {
            switch (tx_type) {
                case 0:
                    ac_balance[account_index] = Apply_deposit(ac_balance[account_index], 
                        amount_cents); break;
                case 1:
                    ac_balance[account_index] = Apply_withdrawal(ac_balance[account_index], 
                        amount_cents); break;
                case 2:
                    ac_balance[account_index] = Apply_fee(ac_balance[account_index], 
                        amount_cents); break;
                case 3:
                    if (interest_type == "SimpleInterest") {
                        ac_balance[account_index] = Simple_interest(amount_cents, apr, days, 
                        day_count_basis, rounding);
                    } else if (interest_type == "CompoundInterest") {
                        ac_balance[account_index] = Compound_amount(amount_cents, apr, years, 
                        compounds_per_year, rounding);                       
                    } else {
                        // DO NOTHING
                    }
                     break;
                case 4:
                    ac_balance[account_index] = Apply_deposit(ac_balance[account_index], 
                        amount_cents); break;
                case 5:
                    ac_balance[account_index] = Apply_withdrawal(ac_balance[account_index], 
                        amount_cents); break;
                default:
                    // DO NOTHING
                    break;
            }
        }
}

void Apply_all(std::string tx_account_id[], int32_t* tx_type, int32_t* tx_amount_cents, 
    const int32_t& tx_count, std::string ac_account_id[], int64_t* ac_balance, 
    const int32_t& ac_capacity, int32_t& ac_count) {
        for (int32_t iter = 0; iter < tx_count; iter++) {
           Apply_one(ac_account_id, ac_balance, ac_capacity, 
           ac_count, tx_account_id[iter], tx_type[iter], tx_amount_cents[iter]);
        }
}

int64_t Balance_of(std::string ac_account_id[], int64_t* ac_balance, int32_t& ac_count, 
    const std::string& account_id) {
        int32_t account_index = Find_account_index(ac_account_id, ac_count, account_id);
        if (account_index == -1) {
            return 0;
        } 
        return ac_balance[account_index];      
}

void Bank_summary(int32_t* tx_type, int32_t* tx_amount_cents, const int32_t& tx_count,
    int64_t* ac_balance, const int32_t& ac_count, int64_t& out_total_deposits,
    int64_t& out_total_withdrawals, int64_t& out_total_fees,
    int64_t& out_total_interest, int64_t& out_net_exposure) {
        for (int32_t iter = 0; iter < tx_count; iter++) {
            switch (iter) {
                case 0:
                case 4:
                    out_total_deposits = 0;
                    out_total_deposits = tx_amount_cents[0] + tx_amount_cents[4];
                    break;
                case 1:
                case 5:
                    out_total_withdrawals = 0;
                    out_total_withdrawals = tx_amount_cents[1] + tx_amount_cents[5];
                    break;   
                case 2:
                    out_total_fees = 0;
                    out_total_fees = tx_amount_cents[2]; break;
                case 3:
                    out_total_interest = 0;
                    out_total_interest = tx_amount_cents[3]; break;      
                default:
                    // DO NOTHING  
                    break;                   
            }
        }

        for (int32_t iter = 0; iter < ac_count; iter++) {
            out_net_exposure += ac_balance[iter];
        }
}

