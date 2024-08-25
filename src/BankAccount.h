#pragma once

#include <iostream>

#include "FileManager.h"
#include "Login.h"
#include "PasswordManager.h"
#include "Transactions.h"

using namespace std;

// Main class, projects root
class BankAccount {
 private:
  PasswordManager passwordManager;
  Login login;
  Transaction transaction;
  FileManager manager;

 public:
  void addBalance() {
    transaction.addBalance();
  }

  void takeAway() {
    transaction.takeAway();
  }

  void showBalance() {
    transaction.showBalance();
  }

  bool checkLogin() {
    return login.checkLogin();
  }

  bool checkPassword() {
    return passwordManager.checkPassword();
  }

  void showTransactionHistory() {
    transaction.showTransactionHistory();
  }

  void clearTransactionHistory() {
    transaction.clearTransactionHistory();
  }

  bool checkTransaction() {
    return transaction.hasTransactions();
  }

  void showMenu() {
    cout << "Choose the action:" << endl;
    cout << "1 - show the balance" << endl;
    cout << "2 - add to the balance" << endl;
    cout << "3 - take away from the balance" << endl;

    if (!transaction.hasTransactions()) {
      cout << "4 - show transaction history" << endl;
      cout << "5 - clear transaction history" << endl;
    }

    cout << "7 - exit" << endl;
  }
};