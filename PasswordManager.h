#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include "FileManager.h"
using namespace std;
//That class manages password
class PasswordManager {
private:
    string password;
    const string passowrdFile = "Password.txt";

    // That function make password, if it doesn't exists
    void makePassword() {
        cout << "You need to create a new password: ";
        cin >> password;
        FileManager::writeLine(passowrdFile, password);
    }

public:
    // Constructor that defines the password
    PasswordManager() {
        if (!FileManager::readFile(passowrdFile, password)) {
            makePassword();
        }
    }
    // That function is defined if password exists
    bool passwordIsExist() {
        if (password.empty() || password == " ") {
            return false;
        }
        return true;
    }

    // That function check user enter the valid password
    bool checkPassword() {
        if (!passwordIsExist()) {
            makePassword();
        }

        string enteredPassword;
        char ch;
        cout << "Enter the password: ";
        ch = _getch();

        while (ch != 13) {
            enteredPassword.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        if (enteredPassword == password) {
            cout << " Correct" << endl;
            return true;
        }
        else {
            cout << " Incorrect" << endl;
            return false;
        }
        return false;
    }
};