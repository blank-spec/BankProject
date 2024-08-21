#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include "FileManager.h"
using namespace std;


struct HashPassword {
    size_t operator()(const string& password) const {
        string reversedPassword = password;
        reverse(reversedPassword.begin(), reversedPassword.end());
        auto hash1 = hash<string>{}(reversedPassword);
        auto hash2 = hash<string>{}(password);

        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash2 << 2));
    }
};

//That class manages password
class PasswordManager {
private:
    string password;
    const string passwordFile = "Password.txt";
    HashPassword hashPass;

    // That function make password, if it doesn't exists
    void makePassword() {
        cout << "You need to create a new password: ";
        cin >> password;
        size_t hashedPassword = hashPass(password);
        FileManager::writeLine(passwordFile, to_string(hashedPassword));
        password = to_string(hashedPassword);
    }

public:
    // Constructor that defines the password
    PasswordManager() {
        if (!FileManager::readFile(passwordFile, password)) {
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

        cout << "Enter the password: ";
        string enteredPassword;
        char ch;
        while ((ch = _getch()) != 13) { 
            if (ch == 8) { 
                if (!enteredPassword.empty()) {
                    enteredPassword.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                enteredPassword += ch;
                cout << '*';
            }
        }
        cout << endl;

        size_t hashedPassword = hashPass(enteredPassword);

        
        if (to_string(hashedPassword) == password) {
            cout << "Correct" << endl;
            return true;
        }
        return false;
    }
};
