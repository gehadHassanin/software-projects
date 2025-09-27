/**
 * @file portfolio.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * 
 */

#ifndef ROBOBANK_PORTFOLIO_PORTFOLIO_H_
#define ROBOBANK_PORTFOLIO_PORTFOLIO_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdint.h>

#define kMaxAudit (256)

enum AccountType : uint8_t {
    kChecking, 
    kSaving,
};

enum TxKind : uint8_t {
    kDeposit,
    kWithdrawal,
    kFee,
    kInterest,
    kTransferIn,
    kTransferOut,
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
    TxRecord(TxKind kind, int64_t amount, 
        int64_t time_stamp,std::string note, 
        std::string id);
    TxKind kind;
    int64_t amount;
    int64_t time_stamp;
    std::string note;
    std::string id;
};

struct TransferRecord {
 public:
    std::string from_id;
    std::string to_id;
    int64_t amount;
    int64_t time_stamp;
    std::string note;
};

class IAccount {
 public:
    virtual std::string Id() const = 0;
    virtual int64_t Balance() const = 0;
    virtual double Apr() const = 0;
    virtual int16_t Audit_size() const = 0;
    virtual const TxRecord& Audit_data() const = 0;
    virtual void Deposit(int64_t amount, int64_t ts, 
        std::string note = nullptr) = 0;
    virtual void Withdraw(int64_t amount, int64_t ts,
        std::string note = nullptr) = 0;
    virtual void Fee(int64_t amount, int64_t ts,
        std::string note = nullptr) = 0; 
    virtual void SimpleInterest(int32_t days, int32_t basis, 
        int64_t ts, std::string note = nullptr) = 0;
    virtual void Apply(const TxRecord& tx) = 0;
};

class BaseAccount : public IAccount {
 public:
    BaseAccount(std::string id, 
        const AccountSetting& setting, 
        int64_t balance = 0);
    std::string Id() const override;
    int64_t Balance() const override;
    double Apr() const override;
    int16_t Audit_size() const override;
    const TxRecord& Audit_data() const override;
    void Deposit(int64_t amount, int64_t ts, 
        std::string note = nullptr) override;
    void Withdraw(int64_t amount, int64_t ts,
        std::string note = nullptr) override;
    void Fee(int64_t amount, int64_t ts,
        std::string note = nullptr) override;
    void SimpleInterest(int32_t days, int32_t basis, 
        int64_t ts, std::string note = nullptr) override;
    void Apply(const TxRecord& tx) override;
    virtual AccountType Type() const = 0;
 protected:
    std::string id_;
    int64_t balance_;
    AccountSetting setting_;
    std::vector<TxRecord> audit_;
    void Record__(TxKind kind, int64_t amount, 
        int64_t ts, std::string note);
};

class CheckingAccount : public BaseAccount {
 public:
    CheckingAccount(std::string id, 
        const AccountSetting& setting, 
        int64_t balance = 0);
    AccountType Type() const override;
};

class SavingsAccount : public BaseAccount {
 public:
    SavingsAccount(std::string id, 
        const AccountSetting& setting, 
        int64_t balance = 0); 
    AccountType Type() const override;
};

class Portfolio {
 public:
    static void Add(std::unique_ptr<IAccount> account);
    static std::unique_ptr<IAccount>& Get(const std::string& id);
    static int32_t Count_accounts();
    static void Apply_all(const std::vector<TxRecord>& records);
    static void Apply_from_ledger(const TxKind trans_type[], int32_t amount[], 
        int64_t time_stamp[], std::string note[],
        std::string id[], int32_t count);
    static bool transfer(TransferRecord tr);
    static int64_t total_exposure();
 private:
    using accounts_map = std::unordered_map<std::string,
    std::unique_ptr<IAccount>>;
    static accounts_map accounts_;
    static std::vector<TxRecord> audit_;
    static bool Is_find__(const std::string& id);
    static void RecordTransaction__(TxKind kind, int64_t amount, 
        int64_t ts, std::string note, const std::string& id);
}; 

#endif  //  ROBOBANK_PORTFOLIO_PORTFOLIO_H_
