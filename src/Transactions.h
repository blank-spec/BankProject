#pragma once
#include <format>
#include <string>

#include "BankComponents.h"
#include "FileManager.h"

// That class is emplements main functional
class Transaction : public ITransactions {
 private:
  double balance;
  const string TRANSACTIONFILE = "Transactions.txt";
  const string BALANCEFILE = "Balance.txt";
  string transaction;
  string warning;
  FileManager manager;

  double getValidAmount(const string& prompt) const {
    double amount;
    cout << prompt;
    while (!(cin >> amount) || amount < 0) {
      cout << "Please enter a valid number" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << prompt;
    }
    return amount;
  }

 public:
  // Constructor that defines the balance
  Transaction() : balance(0), transaction(" ") {
    manager.readFile(BALANCEFILE, balance);

    if (balance < 0) {
      balance = 0;
    }
  }

  // Function for add to balance, also records transaction history
  void addBalance() override {
    double amount = getValidAmount("How much would you add to the balance? ");
    balance += amount;
    FileManager::writeFile(BALANCEFILE, balance);
    FileManager::writeFile(
        TRANSACTIONFILE, format("You added to the balance: {}", amount), true);
  }

  // Function for take away balance, also records transaction history
  void takeAway() override {
    double amount =
        getValidAmount("How much would you take away from the balance? ");
    if (amount > balance) {
      cout << "Insufficient balance!" << endl;
      return;
    }
    balance -= amount;
    FileManager::writeFile(BALANCEFILE, balance);
    FileManager::writeFile(TRANSACTIONFILE,
                           format("Taken away from balance: {}", amount), true);
  }
  // Function for show balance
  void showBalance() const override { cout << "Balance: " << balance << endl; }

  // Function for show transaction history
  void showTransactionHistory() const override {
    FileManager::readAllFile(TRANSACTIONFILE);
  }

  // Function for clear transaction history
  void clearTransactionHistory() const override {
    FileManager::deleteContentInFile(
        TRANSACTIONFILE, "Do you wont to delete transaction history? ",
        "Transaction history clear ");
  }
  // Check if transaction file is empty
  bool hasTransactions() const override {
    return FileManager::checkContent(TRANSACTIONFILE);
  }
};
