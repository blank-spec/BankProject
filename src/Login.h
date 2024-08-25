#pragma once
#include <iostream>

#include "FileManager.h"

using namespace std;

// That class manages login
class Login {
 private:
  const string FILENAME = "Loggin.txt";
  string login;

  // That function make login, if it doesn't exists
  void createLogin() {
    cout << "You need to create a new login: ";
    cin >> login;
    FileManager::writeLine(FILENAME, login);
  }

 public:
  // Constructor that defines the login
  Login() {
    if (!FileManager::readFile(FILENAME, login)) {
      createLogin();
    }
  }
  // That function is defined if login exists
  bool loginIsExist() {
    return !login.empty() && login != " ";
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
