#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include "CurrentTime.h"
using namespace std;

// Class manages files
class FileManager {
public:
    
    // Function for get first line in the file
    template <typename T>
    static bool readFile(const string& fileName, T& content) {
        ifstream file(fileName);
        if (!file.is_open()) {
            return false;
        }

        if (!(file >> content)) {
            return false;
        }

        file.close();
        return true;
    }

    // Function to write to or create a file
    template <typename T>
    static bool writeLine(const string& fileName, const T& content) {
        ofstream file(fileName);
        if (!file.is_open()) {
            return false;
        }
        file << content << endl;
        file.close();
        return true;
    }

    // The function of adding content to a file, for example, transaction history.
    template <typename T>
    static bool addLine(const std::string& fileName, T& content, const std::string& message) {
        std::ofstream file(fileName, std::ios::app);
        if (!file.is_open()) {
            return false;
        }

        Time timeObject;
        std::string time = timeObject.getTime();

        std::stringstream ss;
        ss << time << " " << message << " " << content;

        file << ss.str() << std::endl;
        file.close();
        return true;
    }

    // Function for read all file
    static bool readAllFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            cout << "==============" << endl;
            cout << line << endl;
        }

        file.close();
        return true;
    }

    // Function for clear file
    static bool deleteContentInFile(const string& fileName, const string& warning, const string& end) {
        ofstream file;
        string userChoice;

        cout << warning;
        cin >> userChoice;

        if (userChoice == "yes") {
            file.open(fileName, ios::trunc);
            file.close();
            cout << end << endl;
            return true;
        }
        else if (userChoice == "no") {
            return false;
        }
        else {
            cerr << "Incorrect input" << endl;
            return false;
        }
    }

    // Function to check if file is empty
    static bool checkContent(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            return false;
        }

        string line;
        bool hasContent = true;
        while (getline(file, line)) {
            hasContent = false;
        }

        file.close();
        return hasContent;
    }
    
};
