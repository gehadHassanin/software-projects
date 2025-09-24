/**
 * @file account.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */

#ifndef ROBOBANK_ACCOUNT_ACCOUNT_H_
#define ROBOBANK_ACCOUNT_ACCOUNT_H_

#include <stdint.h>

#define kMaxAudit (256)

enum AccountType : uint8_t {
    kChecking, 
    kSaving,
};

enum TxKind : uint8_t{
    kDeposit,
    kWithdrawal,
    kFee,
    kInterest,
};

struct AccountSetting {
 public:
    AccountType type;
    double apr;
    int64_t fee_flat;
};

struct TxRecord {
 public:
    TxRecord() = default;
    TxRecord(TxKind kind, int64_t amount, int64_t time_stamp,
        const char* note);
    TxKind kind;
    int64_t amount;
    int64_t time_stamp;
    const char* note;
};

class Account {
 public:
    Account(const char* id, const AccountSetting& setting, 
        int64_t balance = 0);
    const char* Id() const;
    const int64_t Balance() const;
    AccountType Type() const;
    double Apr() const;
    int16_t Audit_size() const;
    const TxRecord& Audit_data() const;
    void Deposit(int64_t amount, int64_t ts, 
        const char* note = nullptr);
    void Withdraw(int64_t amount, int64_t ts,
        const char* note = nullptr);
    void Fee(int64_t amount, int64_t ts,
        const char* note = nullptr); 
    void SimpleInterest(int32_t days, int32_t basis, int64_t ts,
        const char* note = nullptr);
    void Apply(const TxRecord& tx);  
 private:
    const char* id_;
    int64_t balance_;
    AccountSetting setting_;
    TxRecord audit_[kMaxAudit];
    int16_t audit_count_;
    void Record__(TxKind kind, int64_t amount, int64_t ts,
    const char* note);
};
#endif  //  ROBOBANK_ACCOUNT_ACCOUNT_H_