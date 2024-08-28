#include <memory>

#include "src/BankAccount.h"
#include "src/BankComponents.h"
#include "src/Interface.h"
#include "src/Login.h"
#include "src/PasswordManager.h"
#include "src/Transactions.h"

using namespace std;

int main() {
  unique_ptr<IPassword> passwordManager = make_unique<PasswordManager>();
  unique_ptr<ILogin> login = make_unique<Login>();
  unique_ptr<ITransactions> transactions = make_unique<Transaction>();

  unique_ptr<IBankAccount> bankAccount = make_unique<BankAccount>(
      move(passwordManager), move(login), move(transactions));

  Interface ui(move(bankAccount));
  ui.showInterface();

  return 0;
}
