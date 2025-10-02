/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */

#include <stdint.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "portfolio.h"

int main() {
    std::string transaction;
    std::string id;
    std::string from_id;
    std::string to_id;
    std::string out;
    int32_t type;
    int32_t counts;
    int64_t amount;
    int64_t time_stamp;
    std::string note;
    double apr;
    int64_t fee_flat;
    int64_t balance;
    std::vector<TxRecord> records;
    TxKind trans_type[MAX_AUDIT];
    int32_t amounts[MAX_AUDIT]; 
    int64_t ts[MAX_AUDIT]; 
    std::string notes[MAX_AUDIT];
    std::string ids[MAX_AUDIT];


    std::cout << "I'm here to help you to add your account into portfolio...\n";
    std::cout << "You can choose any transaction you want to do from this list..\n";
    std::cout << "========================================\n";
    std::cout << "1) AddAccount\n";
    std::cout << "2) GetAccount\n";
    std::cout << "3) CountAccounts\n";
    std::cout << "4) ApplyAll \n";
    std::cout << "5) ApplyFromLedger \n";
    std::cout << "6) Transfer \n";
    std::cout << "7) TotalExposure\n";
    std::cout << "========================================\n";
    std::cout << "Please enter your choice: ";

    while(1) {
        std::cin >> transaction;
        if (transaction == "AddAccount") {
            std::cout << "please, enter your id: ";
            std::cin >> id;
            std::cout << "please, enter your account type: ";
            std::cin >> type; 
            std::cout << "please, enter your balance: ";
            std::cin >> balance; 
            std::cout << "please, enter apr of your account: ";
            std::cin >> apr;                  
            std::cout << "please, enter feet flat of your account: ";
            std::cin >> fee_flat;
            AccountSetting setting;
            setting.apr = apr;
            setting.fee_flat = fee_flat;
            if (type == kChecking) {
                setting.type = kChecking;
                Portfolio::Add(std::make_unique<CheckingAccount>(id, setting, balance));
            }  else if (type == kSaving) {
                setting.type = kSaving;
                Portfolio::Add(std::make_unique<SavingsAccount>(id, setting, balance));
            }          
        } else if (transaction == "GetAccount") {
            std::cout << "please, enter your id: ";
            std::cin >> id;
            std::unique_ptr<IAccount>& ret_account = Portfolio::Get(id);
            std::cout << "Do you want to appear info of your account? (yes/no): ";
            std::cin >> out;
            if (out == "yes") {
                std::cout << "id = " << ret_account->Id() << std::endl;
                std::cout << "balance = " << ret_account->Balance() << std::endl;
                std::cout << "apr = " << ret_account->Apr() << std::endl;
            } else {
                // DO NOTHING
            }
        } else if (transaction == "CountAccounts") {
            std::cout << "number of accounts = " << 
            Portfolio::CountAccounts() << std::endl;
        } else if (transaction == "ApplyAll") {
            std::cout << "please, enter num of records: ";
            std::cin >> counts;
            for (int32_t iter = 0; iter < counts; iter++) {
                std::cout << "please, enter type of transaction: ";
                std::cin >> type;
                std::cout << "please, enter amount: ";
                std::cin >> amount;
                std::cout << "please, enter time stamp: ";
                std::cin >> time_stamp;
                std::cout << "please, enter note: ";
                std::cin >> note;
                std::cout << "please, enter your id: ";
                std::cin >> id;
                records.push_back(TxRecord((TxKind)type, amount, 
                time_stamp, note, id));
            }
            Portfolio::ApplyAll(records);
        } else if (transaction == "ApplyFromLedger") {
            std::cout << "please, enter num of records: ";
            std::cin >> counts;
            for (int32_t iter = 0; iter < counts; iter++) {
                std::cout << "please, enter type of transaction: ";
                std::cin >> type;
                std::cout << "please, enter amount: ";
                std::cin >> amount;
                std::cout << "please, enter time stamp: ";
                std::cin >> time_stamp;
                std::cout << "please, enter note: ";
                std::cin >> note;
                std::cout << "please, enter your id: ";
                std::cin >> id;
                trans_type[iter] = (TxKind)type;
                amounts[iter] = amount;
                ts[iter] = time_stamp;
                notes[iter] = note; 
                ids[iter] = id;
            }
            Portfolio::ApplyFromLedger(trans_type, amounts, 
            ts, notes, ids, counts);
        } else if (transaction == "Transfer") {
            std::cout << "please, enter your from id: ";
            std::cin >> from_id;
            std::cout << "please, enter your to id: ";
            std::cin >> to_id;
            std::cout << "please, enter amount: ";
            std::cin >> amount;
            std::cout << "please, enter time stamp: ";
            std::cin >> time_stamp;
            std::cout << "please, enter note: ";
            std::cin >> note;
            TransferRecord tr = {from_id, to_id, amount, time_stamp, note};
            if(Portfolio::Transfer(tr)) {
                std::cout << "Do you want to appear new balances of accounts? (yes/no): ";
                std::cin >> out;
                if (out == "yes") {
                    std::unique_ptr<IAccount>& from_account = Portfolio::Get(from_id);
                    std::unique_ptr<IAccount>& to_account = Portfolio::Get(to_id);
                    std::cout << "balance account(1) = " << 
                    from_account->Balance() << std::endl;
                    std::cout << "balance account(2)= " << 
                    to_account->Balance() << std::endl;
                } else {
                    // DO NOTHING
                }
            } else {
                std::cout << "transfer failed\n";
            }
        } else if (transaction == "TotalExposure") {
            std::cout << "Total exposure= " << 
            Portfolio::TotalExposure() << std::endl;
        } else {
            // DO NOTHING
        }
        std::cout << "Would you like to perform another transaction? (yes/no): ";
        std::cin >> transaction;
        if (transaction == "yes") {
            std::cout << "Please enter your choice: ";
        } else {
            std::cout << "End of transaction......\n";
        }
    }
    return 0;
}