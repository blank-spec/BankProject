#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "BankAccount.h"
#include "BankComponents.h"
#include "FileManager.h"

using namespace std;
// Class manages inteface
class Interface {
 private:
  unique_ptr<IBankAccount> bank;

 public:
  Interface(unique_ptr<IBankAccount> bank) : bank(move(bank)) {}
  void showInterface() {
    char choice;
    int tries = 0;
    bool running = true;

    while (!bank->checkLogin() || !bank->checkPassword()) {
      cout << "Incorrect password or login, please try again" << endl;
      ++tries;
      if (tries == 5) {
        cout << "Too many failed attempts. Exiting program." << endl;
        return;
      }
    }

    while (running) {
      bank->showMenu();
      cin >> choice;

      switch (choice) {
        case '1':
          bank->showBalance();
          break;
        case '2':
          bank->addBalance();
          break;
        case '3':
          bank->takeAway();
          break;
        case '4':
          if (bank->checkTransaction()) {
            cerr << "Unable to show transaction history." << endl;
            break;
          }
          bank->showTransactionHistory();
          break;
        case '5':
          if (bank->checkTransaction()) {
            cerr << "Unable to clear transaction history." << endl;
            break;
          }
          bank->clearTransactionHistory();
          break;
        case '7':
          running = false;
          break;
        default:
          bank->showBalance();
          break;
      }
    }
  }
};
