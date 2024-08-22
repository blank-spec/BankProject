#pragma once
#include <cstddef>
#include <functional>
#include <random>
#include <string>

#include "FileManager.h"

using namespace std;

class Hasher {
 public:
  static const int SIZESALT = 16;  ///< Length of the salt.

 private:
  static const string CHARACTERS;  ///< Characters used to generate the salt.

  // Generates a random index to pick a character for the salt.
  static int genRandom() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, CHARACTERS.length() - 1);

    return dis(gen);
  }

  static string insertSaltBetweenChars(const string& password, const string& salt) {
    string result;
    size_t saltLength = salt.length();

    for (size_t i = 0; i < password.length(); ++i) {
      result += password[i];
      if (i < saltLength) {
        result += salt[i];
      }
    }

    // Append any remaining salt
    if (saltLength > password.length()) {
      result += salt.substr(password.length());
    }

    return result;
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

  struct HashData {
    // Hashes the input data combined with the salt.
    string operator()(const string& data, const string& salt) {
      string saltedData = insertSaltBetweenChars(data, salt);
      return to_string(hash<string>{}(saltedData));
    }
  };
};

// Define the characters used for generating the salt
inline const string Hasher::CHARACTERS =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!@#$%^&*()-_=+[]{}|;:',.<>?/";
