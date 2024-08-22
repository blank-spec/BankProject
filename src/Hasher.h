#pragma once
#include <cstddef>
#include <functional>
#include <random>
#include <string>

#include "FileManager.h"

using namespace std;

class Hasher {
 private:
  static const int SIZESALT = 16;  ///< Length of the salt.
  static const string CHARACTERS;  ///< Characters used to generate the salt.

  // Generates a random index to pick a character for the salt.
  static int genRandom() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, CHARACTERS.length() - 1);

    return dis(gen);
  }

 public:
  // Generates a random salt string of length SIZESALT.
  static string generateSalt() {
    string salt;
    for (int i = 0; i < SIZESALT; ++i) {
      salt += CHARACTERS[genRandom()];
    }

    return salt;
  }

  struct HashDate {
    // Hashes the input data combined with the salt.
    string operator()(const string& data, const string& salt) {
      string saltedData = salt + data;
      return to_string(hash<string>{}(saltedData));
    }
  };
};

// Define the characters used for generating the salt
const string Hasher::CHARACTERS =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!@#$%^&*()-_=+[]{}|;:',.<>?/";
