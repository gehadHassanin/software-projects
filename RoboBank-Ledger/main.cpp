/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <string>
#include <memory>

#include "calculator.h"
#include "ledger.h"

float apr;
uint16_t days;
uint16_t years;
std::string interest_type;
uint16_t day_count_basis;
uint16_t  compounds_per_year;
std::string rounding;

int main() {
    constexpr int32_t ac_capacity = 1000;
    std::string account_id;
    constexpr int32_t tx_count = 6;
    int32_t tx_amount_cents[tx_count];
    std::string out;
    int32_t type;
    int32_t amount;
    std::string transaction;
    int64_t out_total_deposits;
    int64_t out_total_withdrawals;
    int64_t out_total_fees;
    int64_t out_total_interest;
    int64_t out_net_exposure = 0;
    std::string ac_account_id[] =  {"SAV123", "CHK456", "LOAN789"};
    int64_t ac_balance[] = {1000, 30000, 2000};
    int32_t tx_type[] = {0, 1, 2, 3, 4, 5};
    std::string tx_account_id[] = {"Deposit", "Withdrawal", "Fee", "Interest",
        "TransferIn", "TransferOut"};
    int32_t ac_count = sizeof(ac_account_id) / sizeof(ac_account_id[0]);
    

    std::cout << "Hi, I'm here to help you......." << std::endl;
    std::cout << "You can choose any transaction you want to do from this list..\n";
    std::cout << "========================================\n";
    std::cout << "1) getAccount\n";
    std::cout << "2) createAccount\n";
    std::cout << "3) applyOneTransaction\n";
    std::cout << "4) applyAllTransaction \n";
    std::cout << "5) getBalance \n";
    std::cout << "6) getBank_summary\n";
    std::cout << "========================================\n";
    std::cout << "Please enter your choice: ";

    while(1) {
        std::cin >> transaction;
        if (transaction == "getAccount" | transaction == "createAccount") {
            std::cout << "please, enter account id: ";
            std::cin >> account_id;
            int32_t account_index = Get_or_create_account(ac_account_id, ac_balance, 
            ac_capacity, ac_count, account_id);
            std::cout << "Would you like to appear your account index? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "account index =  " << account_index << std::endl;
            } else {
                //  DO NOTHING
            } 

        } else if (transaction == "applyOneTransaction") {
            std::cout << "please, enter account id: ";
            std::cin >> account_id;
            std::cout << "please, enter type from 0 into 5: ";
            std::cin >> type;
            if (type == 3) {
                std::cout << "please, enter SimpleInterest or CompoundInterest: ";   
                std::cin >> out;
                if (out == "SimpleInterest") {
                    std::cout << "please, enter the apr: ";
                    std::cin >> apr;
                    std::cout << "please, enter the days and day count basis: ";
                    std::cin >> days >> day_count_basis;
                    std::cout << "please, enter the rounding: ";
                    std::cin >> rounding;
                } else if (out == "CompoundInterest") {
                    std::cout << "please, enter the principal and apr: ";
                    std::cin >> apr;
                    std::cout << "please, enter the years and compounds peryear: ";
                    std::cin >> years >> compounds_per_year;
                    std::cout << "please, enter the rounding: ";
                    std::cin >> rounding;
                } else {
                    // DO NOTHING
                }  
            }
            std::cout << "please, enter amount: ";
            std::cin >> amount;
            Apply_one(ac_account_id, ac_balance, ac_capacity, 
            ac_count, account_id, type, amount);
        } else if (transaction == "applyAllTransaction") {
            std::cout << "please, enter account id: ";
            std::cin >> account_id;
            std::cout << "please, enter type from 0 into 5: ";
            std::cin >> type;
            std::cout << "please, enter the apr: ";
            std::cin >> apr;
            std::cout << "please, enter the days and day count basis: ";
            std::cin >> days >> day_count_basis;
            std::cout << "please, enter the rounding: ";
            std::cin >> rounding;
            std::cout << "please, enter the principal and apr: ";
            std::cin >> apr;
            std::cout << "please, enter the years and compounds peryear: ";
            std::cin >> years >> compounds_per_year;
            for (int32_t iter = 0; iter < tx_count; iter++) {
                std::cout << "please, enter amount: ";
                std::cin >> amount;
                tx_amount_cents[iter] = amount;
            }
            Apply_all(tx_account_id, tx_type, tx_amount_cents, tx_count, 
                ac_account_id, ac_balance, ac_capacity, ac_count);
        } else if (transaction == "getBalance") {
            std::cout << "please, enter account id: ";
            std::cin >> account_id;
            int64_t balance = Balance_of(ac_account_id, ac_balance, ac_count, account_id);
            std::cout << "Would you like to appear your balance? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "account index =  " << balance << std::endl;
            } else {
                //  DO NOTHING
            } 
        } else if (transaction == "getBank_summary") {
            for (int32_t iter = 0; iter < tx_count; iter++) {
                std::cout << "please, enter amount: ";
                std::cin >> amount;
                tx_amount_cents[iter] = amount;
            }
            Bank_summary(tx_type, tx_amount_cents, tx_count,
                ac_balance, ac_count, out_total_deposits,
                out_total_withdrawals, out_total_fees,
                out_total_interest,  out_net_exposure);
            std::cout << "Would you like to appear bank summary? (yes/no): ";  
            std::cin >> out;
            if (out == "yes") {
                std::cout << "total deposits =  " << out_total_deposits << std::endl;
                std::cout << "total withdrawals =  " << out_total_withdrawals << std::endl;
                std::cout << "total fees =  " << out_total_fees << std::endl;
                std::cout << "total interest =  " << out_total_interest << std::endl;
                std::cout << "net exposure =  " << out_net_exposure << std::endl;
            } else {
                //  DO NOTHING
            } 
        } else {
            std::cout << "Sorry, this process not found...";
            std::cout << "you can choose process from the list\n";
        }

        std::cout << "Would you like to perform another transaction? (yes/no): ";
        std::cin >> out;
        if (out == "yes") {
            std::cout << "Please enter your choice: ";
        } else {
            std::cout << "End of transaction......\n";
            return 0;
        }  
    }
}