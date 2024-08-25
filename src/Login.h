#pragma once
#include <iostream>

#include "BankComponents.h"
#include "FileManager.h"

using namespace std;

// That class manages login
class Login : public ILogin {
 private:
  const string FILENAME = "Loggin.txt";
  string login;

  // That function make login, if it doesn't exists
  void createLogin() {
    cout << "You need to create a new login: ";
    cin >> login;
    FileManager::writeFile(FILENAME, login);
  }

 public:
  // Constructor that defines the login
  Login() {
    if (!FileManager::readFile(FILENAME, login)) {
      createLogin();
    }
  }
  // That function is defined if login exists
  bool loginIsExist() const override { return !login.empty() && login != " "; }

  // That function check user enter the valid login
  bool checkLogin() override {
    if (!loginIsExist()) {
      createLogin();
    }

    string enteredLogin;
    cout << "Enter your login: ";
    cin >> enteredLogin;
    return enteredLogin == login;
  }
};