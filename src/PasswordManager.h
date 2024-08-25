#pragma once
#include <conio.h>

#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "BankComponents.h"
#include "FileManager.h"
#include "Hasher.h"

using namespace std;

// That class manages password
class PasswordManager : public IPassword {
 private:
  string password;
  string salt;
  const string FILENAME = "Password.txt";
  Hasher::HashData hasher;
  FileManager manager;

  // That function make password, if it doesn't exists
  void makePassword() {
    cout << "You need to create a new password: ";
    cin >> password;
    salt = Hasher::generateSalt();
    string hashedPassword = hasher(password, salt);
    string storedPassword = format("{}{}", salt, hashedPassword);
    manager.writeFile(FILENAME, storedPassword);
    password = hashedPassword;
  }

 public:
  // Constructor that defines the password
  PasswordManager() {
    if (manager.readFile(FILENAME, password)) {
      salt = password.substr(0, Hasher::SIZESALT);
      password = password.substr(Hasher::SIZESALT);
    } else {
      makePassword();
    }
  }
  // That function is defined if password exists
  bool passwordIsExist() const override {
    return !password.empty() && password != " ";
  }

  // That function check user enter the valid password
  bool checkPassword() override {
    if (!passwordIsExist()) {
      makePassword();
    }

    cout << "Enter the password: ";
    string enteredPassword;
    char ch;
    while ((ch = _getch()) != 13) {
      if (ch == 8) {
        if (!enteredPassword.empty()) {
          enteredPassword.pop_back();
          cout << "\b \b";
        }
      } else {
        enteredPassword += ch;
        cout << '*';
      }
    }
    cout << endl;

    string hashedEnteredPassword = hasher(enteredPassword, salt);

    if (hashedEnteredPassword == password) {
      cout << "Correct" << endl;
      return true;
    }
    return false;
  }
};
