/**
 * @file portfolio-test.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2025-10-3
 *
 * @copyright Copyright (c) 2025
 *
 */


#include "../inc/portfolio.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

class PortfolioTest : public ::testing::Test {
 protected:
  void SetUp() override {
    setting = {kChecking, .05, 0};
    count = 1;
    Portfolio::Add(std::make_unique<SavingsAccount>("gehad", setting, 1000));
  }

  void TestRetrieveAccount(std::unique_ptr<IAccount> &account,
                           int64_t new_balance, std::string id) {
    EXPECT_EQ(account->Id(), id);
    EXPECT_DOUBLE_EQ(account->Apr(), setting.apr);
    EXPECT_EQ(account->Balance(), new_balance);
  }

  void AddAccount(const std::string &new_id, int64_t new_balance) {
    Portfolio::Add(
        std::make_unique<SavingsAccount>(new_id, setting, new_balance));
    count++;
  }

  AccountSetting setting;
  int32_t count;
};

TEST_F(PortfolioTest, RetrieveAccount) {
  auto &account = Portfolio::Get("gehad");
  TestRetrieveAccount(account, 1000, "gehad");
}

TEST_F(PortfolioTest, CountAccounts) {
  AddAccount("hager", 500);
  EXPECT_NE(Portfolio::CountAccounts(), count - 1);
  EXPECT_EQ(Portfolio::CountAccounts(), count);
  auto &account = Portfolio::Get("hager");
  TestRetrieveAccount(account, 500, "hager");
}

TEST_F(PortfolioTest, Transfer) {
  TransferRecord record = {"gehad", "hager", 200, 20250101100000, "atm"};
  AddAccount("hager", 500);

  auto &from_acc = Portfolio::Get("gehad");
  auto &to_acc = Portfolio::Get("hager");

  int64_t init_from_balance = from_acc->Balance();
  int64_t init_to_balance = to_acc->Balance();

  Portfolio::Transfer(record);

  TestRetrieveAccount(from_acc, init_from_balance - 200, "gehad");
  TestRetrieveAccount(to_acc, init_to_balance + 200, "hager");
}
