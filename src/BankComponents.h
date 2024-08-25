#pragma once

#include <string>
using namespace std;

class ILogin {
 public:
  virtual ~ILogin() = default;
  virtual bool loginIsExist() const = 0;
  virtual bool checkLogin() = 0;
};

class IPassword {
 public:
  virtual ~IPassword() = default;
  virtual bool passwordIsExist() const = 0;
  virtual bool checkPassword() = 0;
};

class ITransactions {
 public:
  virtual ~ITransactions() = default;
  virtual void addBalance() = 0;
  virtual void takeAway() = 0;
  virtual void showBalance() const = 0;
  virtual void showTransactionHistory() const = 0;
  virtual void clearTransactionHistory() const = 0;
  virtual bool hasTransactions() const = 0;
};

class IBankAccount {
 public:
  virtual ~IBankAccount() = default;
  virtual void addBalance() = 0;
  virtual void takeAway() = 0;
  virtual void showBalance() = 0;
  virtual bool checkLogin() = 0;
  virtual bool checkPassword() = 0;
  virtual void showTransactionHistory() = 0;
  virtual void clearTransactionHistory() = 0;
  virtual bool checkTransaction() = 0;
  virtual void showMenu() = 0;
};