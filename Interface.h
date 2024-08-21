#pragma once

#include <iostream>
#include "BankAccount.h"
#include <cstdlib>
#include "FileManager.h"
using namespace std;
//Class manages inteface
class Interface {
private:
	BankAccount Bank;

public:
	void showInterface() {
		char choice;
		int tries = 0;

		while (!Bank.checkPassword() || !Bank.checkLogin()) {
			cout << "Incorrect password or login, please try again" << endl;
			++tries;
			if (tries == 5) {
				exit(0);
			}
		}

		for (;;) {
			Bank.showMenu();
			cin >> choice;
			
			switch (choice) {
			case '1':
				Bank.showBalance();
				break;
			case '2':
				Bank.addBalance();
				break;
			case '3':
				Bank.takeAway();
				break;
			case '4':
				if (Bank.checkTransaction() == true) {
					cerr << "Incorrect" << endl;
				}
				else {
					Bank.showTransactionHistory();
				}
				break;
			case '5':
				if (Bank.checkTransaction() == true) {
					cerr << "Incorrect" << endl;
				}
				else {
					Bank.clearTransactionHistory();
				}
				break;
			case '7':
				exit(0);
				break;
			default:
				Bank.showBalance();
				break;
			}
		}
	}
};
