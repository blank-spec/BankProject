#pragma once
#include <conio.h>

#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "FileManager.h"
#include "Hasher.h"

using namespace std;

// That class manages password
class PasswordManager {
 private:
  string password;
  string salt;
  const string passwordFile = "Password.txt";
  Hasher::HashDate hasher;

  // That function make password, if it doesn't exists
  void makePassword() {
    cout << "You need to create a new password: ";
    cin >> password;
    salt = Hasher::generateSalt();
    string hashedPassword = hasher(password, salt);
    string storedPassword = format("{}:{}", salt, hashedPassword);
    FileManager::writeLine(passwordFile, storedPassword);
  }

 public:
  // Constructor that defines the password
  PasswordManager() {
    if (FileManager::readFile(passwordFile, password)) {
      size_t separator = password.find(':');
      salt = password.substr(0, separator);
      password = password.substr(separator + 1);
    } else {
      makePassword();
    }
  }
  // That function is defined if password exists
  bool passwordIsExist() {
    return !password.empty() && password != " ";
  }

  // That function check user enter the valid password
  bool checkPassword() {
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
    cout << hashedEnteredPassword << endl;
    return false;
  }
};
