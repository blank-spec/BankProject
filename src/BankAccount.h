#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

#include "BankComponents.h"

using namespace std;

// Main class, projects root
class BankAccount : public IBankAccount {
 private:
  unique_ptr<IPassword> passwordManager;
  unique_ptr<ILogin> login;
  unique_ptr<ITransactions> transactions;

 public:
  BankAccount(unique_ptr<IPassword> p, unique_ptr<ILogin> lg,
              unique_ptr<ITransactions> tr)
      : passwordManager(move(p)), login(move(lg)), transactions(move(tr)) {}

  void addBalance() override { transactions->addBalance(); }

  void takeAway() override { transactions->takeAway(); }

  void showBalance() override { transactions->showBalance(); }

  bool checkLogin() override { return login->checkLogin(); }

  bool checkPassword() override { return passwordManager->checkPassword(); }

  bool checkTransaction() override { return transactions->hasTransactions(); }

  void showTransactionHistory() override {
    transactions->showTransactionHistory();
  }

  void clearTransactionHistory() override {
    transactions->clearTransactionHistory();
  }

  void showMenu() override {
    cout << "Choose the action:" << endl;
    cout << "1 - show the balance" << endl;
    cout << "2 - add to the balance" << endl;
    cout << "3 - take away from the balance" << endl;

    if (!transactions->hasTransactions()) {
      cout << "4 - show transaction history" << endl;
      cout << "5 - clear transaction history" << endl;
    }

    cout << "7 - exit" << endl;
  }
};
