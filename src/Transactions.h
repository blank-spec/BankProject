#pragma once
#include <string>

#include "FileManager.h"

// That class is emplements main functional
class Transaction {
 private:
  double balance;
  const string transactionFile = "Transactions.txt";
  const string balanceFile = "Balance.txt";
  FileManager fileManager;
  string transaction;
  string warning;

 public:
  // Constructor that defines the balance
  Transaction()
      : balance(0), transaction(" ") {
    FileManager::readFile(balanceFile, balance);
    updateTransaction();

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
    FileManager::writeLine(balanceFile, balance);
    FileManager::addLine(transactionFile, amount, "You added to the balance: ");
    updateTransaction();
  }

  // Function for take away balance, also records transaction history
  void takeAway() {
    double amount;
    cout << "How much you would take away from the the balance? ";

    while (!(cin >> amount) || amount < 0) {
      cout << "Please enter a valid number" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    balance -= amount;

    if (balance < 0 || amount > balance) {
      balance = 0;
    }

    FileManager::writeLine(balanceFile, balance);
    FileManager::addLine(transactionFile, amount, "You take away balacne: ");
    updateTransaction();
  }
  // Function for show balance
  void showBalance() const {
    cout << "Balance: " << balance << endl;
  }

  // Function for show transaction history
  void showTransactionHistory() {
    fileManager.readAllFile(transactionFile);
  }

  // Function for clear transaction history
  void clearTransactionHistory() {
    fileManager.deleteContentInFile(transactionFile, "Do you wont to delete transaction history? ", "Transaction history clear ");
    updateTransaction();
  }
  // Check if transaction file is empty
  bool updateTransaction() {
    return FileManager::checkContent(transactionFile);
  }
};
