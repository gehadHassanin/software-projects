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

#ifndef ROBOBANK_PORTFOLIO_INC_PORTFOLIO_H_
#define ROBOBANK_PORTFOLIO_INC_PORTFOLIO_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#define MAX_AUDIT (256)

/**
 * @brief Enumeration for different account types.
 */
enum AccountType : uint8_t {
  kChecking,
  kSaving,
};

/**
 * @brief Enumeration for transaction kinds
 *        (Deposit, Withdraw, Fee, etc.).
 */
enum TxKind : uint8_t {
  kDeposit,
  kWithdrawal,
  kFee,
  kInterest,
  kTransferIn,
  kTransferOut,
};

/**
 * @brief Holds configuration settings for an account.
 */
struct AccountSetting {
 public:
  AccountType type;  ///< The type of account (e.g., Checking, Savings).
  double apr;  ///< The annual percentage rate (APR) applied to the account.
  int64_t fee_flat;  ///< Flat fee amount applied to transactions.
};

/**
 * @brief Represents a single transaction record in an account's history.
 */
struct TxRecord {
 public:
  /**
   * @brief Constructs a transaction record.
   *
   * @param kind       The type of transaction (Deposit, Withdrawal, Fee, etc.).
   * @param amount     The amount involved in the transaction.
   * @param time_stamp The timestamp of the transaction (epoch time).
   * @param note       A descriptive note about the transaction.
   * @param id         The ID of the account related to this transaction.
   */
  TxRecord(TxKind kind, int64_t amount, int64_t time_stamp, std::string note,
           std::string id);

  TxKind kind;         ///< Transaction type.
  int64_t amount;      ///< Transaction amount.
  int64_t time_stamp;  ///< Transaction timestamp.
  std::string note;    ///< Optional note for transaction details.
  std::string id;      ///< Associated account ID.
};

/**
 * @brief Represents a transfer of funds between two accounts.
 */
struct TransferRecord {
 public:
  std::string from_id;  ///< ID of the source account.
  std::string to_id;    ///< ID of the destination account.
  int64_t amount;       ///< Amount being transferred.
  int64_t time_stamp;   ///< Timestamp of the transfer (epoch time).
  std::string note;     ///< Optional note describing the transfer.
};

/**
 * @class IAccount
 * @brief Abstract interface for all account types.
 *
 * @details Provides the fundamental operations for querying account data
 *          and performing transactions.
 *
 * @note All concrete account types must
 *       implement this interface.
 */
class IAccount {
 public:
  /**
   * @brief Get the account identifier.
   * @return Unique string ID of the account.
   */
  virtual std::string Id() const = 0;

  /**
   * @brief Get the current account balance.
   * @return Current balance in smallest currency unit (e.g., cents).
   */
  virtual int64_t Balance() const = 0;

  /**
   * @brief Get the annual percentage rate (APR).
   * @return APR as a double.
   */
  virtual double Apr() const = 0;

  /**
   * @brief Get the number of audit records.
   * @return Count of stored audit entries.
   */
  virtual int16_t Audit_size() const = 0;

  /**
   * @brief Access the latest audit record.
   * @return Reference to the most recent TxRecord.
   */
  virtual const TxRecord &Audit_data() const = 0;

  /**
   * @brief Deposit funds into the account.
   * @param amount Amount to deposit.
   * @param ts Transaction timestamp.
   * @param note Optional transaction note.
   */
  virtual void Deposit(int64_t amount, int64_t ts, std::string note) = 0;

  /**
   * @brief Withdraw funds from the account.
   * @param amount Amount to withdraw.
   * @param ts Transaction timestamp.
   * @param note Optional transaction note.
   */
  virtual void Withdraw(int64_t amount, int64_t ts, std::string note) = 0;

  /**
   * @brief Apply a fee to the account.
   * @param amount Fee amount.
   * @param ts Transaction timestamp.
   * @param note Optional transaction note.
   */
  virtual void Fee(int64_t amount, int64_t ts, std::string note) = 0;

  /**
   * @brief Apply simple interest to the account.
   * @param days Number of days.
   * @param basis Day count basis (e.g., 360/365).
   * @param ts Transaction timestamp.
   * @param note Optional transaction note.
   */
  virtual void ApplyInterest(int32_t days, int32_t basis, int64_t ts,
                             std::string note) = 0;

  /**
   * @brief Apply a transaction to the account.
   * @param tx Transaction record.
   */
  virtual void Apply(const TxRecord &tx) = 0;
  virtual ~IAccount() = default;
};

/**
 * @class BaseAccount
 * @brief Abstract base implementation of IAccount.
 *
 * @details Provides shared functionality for accounts, such as
 *          storing account ID, balance, settings, and audit records.
 *          Concrete account types (e.g., CheckingAccount, SavingsAccount)
 *
 * @note should inherit from this class and implement Type().
 */
class BaseAccount : public IAccount {
 public:
  /**
   * @brief Construct a new BaseAccount.
   * @param id Account identifier.
   * @param setting Account configuration settings.
   * @param balance Initial account balance (default = 0).
   */
  BaseAccount(std::string id, const AccountSetting &setting,
              int64_t balance = 0);
  std::string Id() const override;
  int64_t Balance() const override;
  double Apr() const override;
  int16_t Audit_size() const override;
  const TxRecord &Audit_data() const override;
  void Deposit(int64_t amount, int64_t ts, std::string note = nullptr) override;
  void Withdraw(int64_t amount, int64_t ts,
                std::string note = nullptr) override;
  void Fee(int64_t amount, int64_t ts, std::string note = nullptr) override;
  void ApplyInterest(int32_t days, int32_t basis, int64_t ts,
                     std::string note = nullptr) override;
  void Apply(const TxRecord &tx) override;

  /**
   * @brief Get the type of this account.
   * @return AccountType enumeration value.
   */
  virtual AccountType Type() const = 0;

 protected:
  std::string id_;               ///< Account identifier
  int64_t balance_;              ///< Current balance
  AccountSetting setting_;       ///< Account settings
  std::vector<TxRecord> audit_;  ///< List of audit records

  /**
   * @brief Record a transaction in the audit log.
   * @param kind Type of transaction (Deposit, Withdraw, Fee, etc.).
   * @param amount Transaction amount.
   * @param ts Timestamp of transaction.
   * @param note Optional transaction note.
   */
  void Record__(TxKind kind, int64_t amount, int64_t ts, std::string note);
};

/**
 * @class CheckingAccount
 * @brief Concrete implementation of a checking account.
 *
 * @details Inherits from BaseAccount and represents a checking account type.
 *          Provides specific behavior such as identifying itself as a
 *          checking account through the Type() method.
 */
class CheckingAccount : public BaseAccount {
 public:
  /**
   * @brief Construct a new CheckingAccount.
   * @param id Account identifier.
   * @param setting Account configuration settings.
   * @param balance Initial account balance (default = 0).
   */
  CheckingAccount(std::string id, const AccountSetting &setting,
                  int64_t balance = 0);

  ~CheckingAccount() override = default;

  /**
   * @brief Get the type of this account.
   * @return AccountType::Checking
   */
  AccountType Type() const override;
};

/**
 * @class SavingsAccount
 * @brief Concrete implementation of a checking account.
 *
 * @details Inherits from BaseAccount and represents a checking account type.
 *          Provides specific behavior such as identifying itself as a
 *          checking account through the Type() method.
 */
class SavingsAccount : public BaseAccount {
 public:
  /**
   * @brief Construct a new SavingsAccount.
   * @param id Account identifier.
   * @param setting Account configuration settings.
   * @param balance Initial account balance (default = 0).
   */
  SavingsAccount(std::string id, const AccountSetting &setting,
                 int64_t balance = 0);

  ~SavingsAccount() override = default;

  /**
   * @brief Get the type of this account.
   * @return AccountType::Savings
   */
  AccountType Type() const override;
};

/**
 * @class Portfolio
 * @brief Manages a collection of financial accounts and their transactions.
 *
 * @details The Portfolio class acts as a centralized manager for multiple accounts.
 *          It supports adding and retrieving accounts, applying transactions from
 *          records or ledgers, transferring funds between accounts, and tracking
 *          total exposure.
 *
 */
class Portfolio {
 public:
  /**
   * @brief Add a new account to the portfolio.
   * @param account A unique pointer to the account to be added.
   */
  static void Add(std::unique_ptr<IAccount> account);

  /**
   * @brief Get an account by its identifier.
   * @param id The account identifier.
   * @return Reference to a unique pointer of the requested account.
   * @throws std::out_of_range if the account does not exist.
   */
  static std::unique_ptr<IAccount> &Get(const std::string &id);

  /**
   * @brief Count the number of accounts in the portfolio.
   * @return Number of accounts.
   */
  static int32_t CountAccounts();

  /**
   * @brief Apply a batch of transaction records to the appropriate accounts.
   * @param records Vector of transaction records.
   */
  static void ApplyAll(const std::vector<TxRecord> &records);

  /**
   * @brief Apply a batch of transactions from ledger arrays.
   *
   * Each array element corresponds to the same transaction index.
   *
   * @param trans_type Array of transaction kinds.
   * @param amount Array of transaction amounts.
   * @param time_stamp Array of transaction timestamps.
   * @param note Array of transaction notes.
   * @param id Array of account IDs to apply the transactions to.
   * @param count Number of transactions in the arrays.
   */
  static void ApplyFromLedger(const TxKind trans_type[], int32_t amount[],
                              int64_t time_stamp[], std::string note[],
                              std::string id[], int32_t count);

  /**
   * @brief Transfer funds between accounts.
   * @param tr A transfer record containing source, destination, and amount.
   * @return true if the transfer was successful, false otherwise.
   */
  static bool Transfer(TransferRecord tr);

  /**
   * @brief Get the total exposure across all accounts.
   * @return The total exposure as a 64-bit integer.
   */
  static int64_t TotalExposure();

 private:
  using AccountsMap =
      std::unordered_map<std::string, std::unique_ptr<IAccount>>;

  ///  Collection of accounts managed by this portfolio.
  static AccountsMap accounts_;

  ///  Global audit log of transactions applied to the portfolio.
  static std::vector<TxRecord> audit_;

  /**
   * @brief Check if an account exists.
   * @param id The account identifier.
   * @return true if the account exists, false otherwise.
   */
  static bool Is_find__(const std::string &id);

  /**
   * @brief Record a transaction in the global audit log.
   * @param kind Type of transaction.
   * @param amount Transaction amount.
   * @param ts Transaction timestamp.
   * @param note Transaction note.
   * @param id Account identifier the transaction applies to.
   */
  static void RecordTransaction__(TxKind kind, int64_t amount, int64_t ts,
                                  std::string note, const std::string &id);
};

#endif  //  ROBOBANK_PORTFOLIO_INC_PORTFOLIO_H_
