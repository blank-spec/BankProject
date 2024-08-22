#pragma once
#include <iostream>

#include "FileManager.h"

using namespace std;

// That class manages login
class Login {
 private:
  const string fileName = "Credit.txt";
  string login;

  // That function make login, if it doesn't exists
  void createLogin() {
    cout << "You need to create a new login: ";
    cin >> login;
    FileManager::writeLine(fileName, login);
  }

 public:
  // Constructor that defines the login
  Login() {
    if (!FileManager::readFile(fileName, login)) {
      createLogin();
    }
  }
  // That function is defined if login exists
  bool loginIsExist() {
    if (login.empty() || login == " ") {
      return false;
    }
    return true;
  }

  // That function check user enter the valid login
  bool checkLogin() {
    if (!loginIsExist()) {
      createLogin();
    }

    string enteredLogin;
    cout << "Enter your login: ";
    cin >> enteredLogin;
    return enteredLogin == login;
  }
};
