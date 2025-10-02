/**
 * @file portfolio.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */

#include "portfolio.h"

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "calculator.h"


std::unordered_map<std::string, std::unique_ptr<IAccount>> Portfolio::accounts_;
std::vector<TxRecord> Portfolio::audit_;

TxRecord::TxRecord(TxKind kind, int64_t amount, 
    int64_t time_stamp, std::string note, 
    std::string id) : kind(kind), amount(amount),
    time_stamp(time_stamp), note(note), id(id) {}

BaseAccount::BaseAccount(std::string id, 
    const AccountSetting& setting,int64_t balance)  
    : id_(id), setting_(setting), balance_(balance) {}

std::string BaseAccount::Id() const { return id_; }

int64_t BaseAccount::Balance() const { return balance_; }

AccountType BaseAccount::Type() const { return setting_.type; }

double BaseAccount::Apr() const { return setting_.apr; }

int16_t BaseAccount::Audit_size() const { return audit_.size(); }

const TxRecord& BaseAccount::Audit_data() const 
    { return audit_[audit_.size() - 1]; }

void BaseAccount::Deposit(int64_t amount, int64_t ts, 
    std::string note) {
        balance_  = ApplyDeposit(balance_, amount);
        Record__(kDeposit, amount, ts, note);
}

void BaseAccount::Withdraw(int64_t amount, int64_t ts, 
    std::string note) {
        balance_  = ApplyWithdrawal(balance_, amount);
        Record__(kWithdrawal, amount, ts, note);
}

void BaseAccount::Fee(int64_t amount, int64_t ts, 
    std::string note ) {
        balance_  = ApplyFee(balance_, amount);
        Record__(kFee, amount, ts, note);
}

void BaseAccount::ApplyInterest(int32_t days, int32_t basis, 
    int64_t ts, std::string note) {
        int64_t rate = SimpleInterest(balance_, setting_.apr, days, 
        basis, "HalfUp"); 
        balance_  += rate;
        Record__(kInterest, rate, ts, note);
}

void BaseAccount::Apply(const TxRecord& tx) {
    switch(tx.kind) {
        case kDeposit:
        Deposit(tx.amount, tx.time_stamp, tx.note); break;
        case kWithdrawal:
        Withdraw(tx.amount, tx.time_stamp, tx.note); break;
        case kFee:
        Fee(tx.amount, tx.time_stamp, tx.note); break;
        case kInterest:
        // SimpleInterest(days, basis, tx.time_stamp, tx.note);
        break;
        default:
            // DO NOTHING
            break;
    }
}  

void BaseAccount::Record__(TxKind kind, int64_t amount, int64_t ts,
    std::string note) {
        if (audit_.size() <= MAX_AUDIT) {
            TxRecord tx_record(kind, amount, ts, note, id_); 
            audit_.push_back(tx_record);
        }
}

SavingsAccount::SavingsAccount(std::string id, 
        const AccountSetting& setting, 
        int64_t balance) : BaseAccount(id, setting, balance) {}

CheckingAccount::CheckingAccount(std::string id, 
        const AccountSetting& setting, 
        int64_t balance) : BaseAccount(id, setting, balance) {}

AccountType CheckingAccount::Type() const { return setting_.type; }

AccountType SavingsAccount::Type() const { return setting_.type; }

void Portfolio::Add(std::unique_ptr<IAccount> account) {
    if (!Is_find__(account->Id())) {
        accounts_[account->Id()] = std::move(account);
    } else {
        // DO NOTHING
    }  
}

std::unique_ptr<IAccount>& Portfolio::Get(const std::string& id) {
    return accounts_.at(id);
}

int32_t Portfolio::CountAccounts() {
    return accounts_.size();
}

void Portfolio::ApplyAll(const std::vector<TxRecord>& records) {  
    for (auto& iter : records) {
        if (Is_find__(iter.id)) {
            std::unique_ptr<IAccount>& account = Get(iter.id);
            account->Apply(iter);
            RecordTransaction__(iter.kind, iter.amount, 
            iter.time_stamp, iter.note, iter.id);
        } else {
            // DO NOTHING
        }
    }
}

void Portfolio::ApplyFromLedger(const TxKind trans_type[], int32_t amount[], 
    int64_t time_stamp[], std::string note[],
    std::string id[], int32_t count) {
        std::vector<TxRecord> records;
        for (int32_t iter = 0; iter < count; iter++) {
            TxRecord tx(trans_type[iter], amount[iter], 
            time_stamp[iter], note[iter], id[iter]);
            records.push_back(tx);
        }
        ApplyAll(records);
}

bool Portfolio::Transfer(TransferRecord tr) {
    auto it_fromId = accounts_.find(tr.from_id);
    auto it_toId = accounts_.find(tr.to_id);
    if (it_fromId != accounts_.end() && 
        it_toId != accounts_.end()) {
            std::unique_ptr<IAccount>& to_account = Get(tr.to_id);
            std::unique_ptr<IAccount>& from_account = Get(tr.from_id);
            from_account->Withdraw(tr.amount, tr.time_stamp, tr.note);
            to_account->Deposit(tr.amount, tr.time_stamp, tr.note);
            RecordTransaction__(kWithdrawal, tr.amount, 
            tr.time_stamp, tr.note, from_account->Id());
            RecordTransaction__(kDeposit, tr.amount, 
            tr.time_stamp, tr.note, from_account->Id());
            return true;
    } else {
        return false;
    }   
}

int64_t Portfolio::TotalExposure() {
    int64_t total = 0;
    for (auto& iter : accounts_) {
        total += iter.second->Balance();
    }
    return total;
}

bool Portfolio::Is_find__(const std::string& id) {
    auto it = accounts_.find(id);
    if (it != accounts_.end()) {
        return true;
    } else {
        return false;
    }
}

void Portfolio::RecordTransaction__(TxKind kind, int64_t amount, 
    int64_t ts, std::string note, const std::string& id) {
        if (audit_.size() <= MAX_AUDIT) {
            TxRecord tx_record(kind, amount, ts, note, id); 
            audit_.push_back(tx_record);
        }
}