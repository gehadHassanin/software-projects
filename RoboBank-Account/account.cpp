/**
 * @file account.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */


#include "utils.h"
#include "calculator.h"
#include "account.h"

TxRecord::TxRecord(TxKind kind, int64_t amount, int64_t time_stamp,
    const char* note) : kind(kind), amount(amount),
    time_stamp(time_stamp) , note(note) {}

Account::Account(const char* id, const AccountSetting& setting,
    int64_t balance) : id_(id), setting_(setting), 
    balance_(balance) { audit_count_ = 0; }

const char* Account::Id() const { return id_; }

const int64_t Account::Balance() const { return balance_; }

AccountType Account::Type() const { return setting_.type; }

double Account::Apr() const { return setting_.apr; }

int16_t Account::Audit_size() const { return audit_count_; }

const TxRecord& Account::Audit_data() const 
    { return audit_[audit_count_ - 1]; }

void Account::Deposit(int64_t amount, int64_t ts, 
    const char* note) {
        balance_  = Apply_deposit(balance_, amount);
        Record__(kDeposit, amount, ts, note);
}

void Account::Withdraw(int64_t amount, int64_t ts, 
    const char* note) {
        balance_  = Apply_withdrawal(balance_, amount);
        Record__(kWithdrawal, amount, ts, note);
}

void Account::Fee(int64_t amount, int64_t ts, 
    const char* note ) {
        balance_  = Apply_fee(balance_, amount);
        Record__(kFee, amount, ts, note);
}

void Account::SimpleInterest(int32_t days, int32_t basis, int64_t ts,
    const char* note) {
        int64_t rate = Simple_interest(balance_, setting_.apr, days, 
        basis, "HalfUp"); 
        balance_  += rate;
        Record__(kInterest, rate, ts, note);
}

void Account::Apply(const TxRecord& tx) {
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

void Account::Record__(TxKind kind, int64_t amount, int64_t ts,
    const char* note) {
        if (audit_count_ <= kMaxAudit) {
            TxRecord tx_record(kind, amount, ts, note);
            audit_[audit_count_++] = tx_record;
        }
}
