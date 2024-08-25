#pragma once

#include <cstdlib>
#include <iostream>

#include "BankAccount.h"
#include "FileManager.h"

using namespace std;
// Class manages inteface
class Interface {
 private:
  BankAccount Bank;

 public:
  void showInterface() {
    char choice;
    int tries = 0;
    bool running = true;

    while (!Bank.checkPassword() || !Bank.checkLogin()) {
      cout << "Incorrect password or login, please try again" << endl;
      ++tries;
      if (tries == 5) {
        cout << "Too many failed attempts. Exiting program." << endl;
        return;
      }
    }

    while (running) {
      Bank.showMenu();
      cin >> choice;

      switch (choice) {
        case '1':
          Bank.showBalance();
          break;
        case '2':
          Bank.addBalance();
          break;
        case '3':
          Bank.takeAway();
          break;
        case '4':
          if (Bank.checkTransaction()) {
            cerr << "Unable to show transaction history." << endl;
            break;
          }
          Bank.showTransactionHistory();
          break;
        case '5':
          if (Bank.checkTransaction()) {
            cerr << "Unable to clear transaction history." << endl;
            break;
          }
          Bank.clearTransactionHistory();
          break;
        case '7':
          running = false;
          break;
        default:
          Bank.showBalance();
          break;
      }
    }
  }
};
