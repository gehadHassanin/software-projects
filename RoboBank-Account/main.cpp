/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */

#include <iostream>
#include <string>
#include <memory>

#include "account.h"

int main() {
    std::string out;
    char id[kMaxAudit];
    AccountType account_type;
    uint8_t type;
    double apr;
    int64_t fee_flat;
    int64_t balance;
    int64_t amount;
    int64_t ts; 
    char note[kMaxAudit];
    int32_t days;
    int32_t basis;

    std::cout << "I'm here to help you to create your account...\n";
    std::cout << "Do you want to create your account? (yes/no): ";
    std::cin >> out;
    if (out == "yes") {   
        std::cout << "please, enter your account id: ";
        std::cin >> id;
        std::cout << "please, enter your balance: ";
        std::cin >> balance;
        std::cout << "please, enter your account type: ";
        std::cin >> type;   
        if (type == 0) {
            account_type = kChecking;
        }  else if (account_type == 1) {
            account_type = kSaving;
        }  
        std::cout << "please, enter apr of your account: ";
        std::cin >> apr;                  
        std::cout << "please, enter feet flat of your account: ";
        std::cin >> fee_flat;
        AccountSetting setting;
        setting.apr = apr;
        setting.fee_flat = fee_flat;
        setting.type = account_type;
        Account account(id, setting, balance);
        while(1) {
            std::cout << "Do you want to apply any transaction? (yes/no): ";
            std::cin >> out;
            if (out == "yes") {
                std::cout << "please, enter type of transaction: ";
                std::cin >> type;
                std::cout << "please, enter time stamp: ";
                std::cin >> ts;
                std::cout << "please, enter note: ";
                std::cin >> note;
                switch(type) {
                    case 0: 
                        std::cout << "please, enter amount: ";
                        std::cin >> amount;
                        account.Deposit(amount, ts, note);
                        break;
                    case 1:
                        std::cout << "please, enter amount: ";
                        std::cin >> amount;
                        account.Withdraw(amount, ts, note);
                        break;
                    case 2:
                        std::cout << "please, enter amount: ";
                        std::cin >> amount;
                        account.Fee(amount, ts, note);
                        break;
                    case 3:
                        std::cout << "please, enter days: ";
                        std::cin >> days;
                        std::cout << "please, enter basis: ";
                        std::cin >> basis;
                        account.SimpleInterest(days, basis, ts, note);
                    default:
                        // DO NOTHING
                        break;
                }
            } else {
                break;
            }            
        }
        std::cout << "Do you want to appear your balance? (yes/no): ";
        std::cin>> out;
        if (out == "yes") {
            std::cout << "balance = " << account.Balance() << std::endl;
        } else {
            std::cout << "End of transaction......\n";
        }        
    } else {
        // DO NOTHING
    }
    return 0;
}