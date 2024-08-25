#pragma once
#include <string>

#include "FileManager.h"

// That class is emplements main functional
class Transaction {
 private:
  double balance;
  const string TRANSACTIONFILE = "Transactions.txt";
  const string BALANCEFILE = "Balance.txt";
  string transaction;
  string warning;
  FileManager manager;

 public:
  // Constructor that defines the balance
  Transaction()
      : balance(0), transaction(" ") {
    manager.readFile(BALANCEFILE, balance);

    if (balance < 0) {
      balance = 0;
    }
  }

  // Function for add to balance, also records transaction history
  void addBalance() {
    double amount;
    cout << "How much would you add to the balance? ";

    while (!(cin >> amount) || amount < 0) {
      cout << "Please enter a valid number" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    balance += amount;
    FileManager::writeLine(BALANCEFILE, balance);
    FileManager::addLine(TRANSACTIONFILE, amount, "You added to the balance: ");
  }

  // Function for take away balance, also records transaction history
  void takeAway() {
    double amount;
    cout << "How much would you take away from the balance? ";

    while (!(cin >> amount) || amount < 0) {
      cout << "Please enter a valid number" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    balance -= amount;

    if (amount > balance) {
      cout << "Insufficient balance!" << endl;
      return;
    }

    FileManager::writeLine(BALANCEFILE, balance);
    FileManager::addLine(TRANSACTIONFILE, amount, "Taken away from balance: ");
  }
  // Function for show balance
  void showBalance() const {
    cout << "Balance: " << balance << endl;
  }

  // Function for show transaction history
  void showTransactionHistory() {
    FileManager::readAllFile(TRANSACTIONFILE);
  }

  // Function for clear transaction history
  void clearTransactionHistory() {
    FileManager::deleteContentInFile(TRANSACTIONFILE, "Do you wont to delete transaction history? ", "Transaction history clear ");
  }
  // Check if transaction file is empty
  bool hasTransactions() {
    return FileManager::checkContent(TRANSACTIONFILE);
  }
};
