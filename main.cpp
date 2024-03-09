#include "Registration.h"
#include "AccountOpening.h"
#include "bank_transfer.h"

int main() {
  bool exit = false;
  while (exit == false) {
    std::cout << "which bank you choose(SBERBANK, ALPHABANK, TINKOFF) ";
    std::string bank;
    std::cin >> bank;
    std::cin.ignore();
    std::string input;
    std::cout
        << "Hello. What kind of service do you want.(registration, open account, top up, withdraw, close account," \
         "transfer money to another account in our bank,transfer money to another account in other bank, cancel transaction within the bank,"\
         "cancel transaction money to another account in other bank)\n";
    std::getline(std::cin, input);

    if (input == "registration") {
      std::string is_legal;
      std::string legal_subject = "legal person";
      std::cout << "write down which legal entity you are: ";
      std::getline(std::cin, is_legal);

      if (legal_subject == is_legal) {
        IBankManager *phys_bank_manager = new CreaterPhysicalPerson;
        std::cout << "\n Write name: ";
        phys_bank_manager->WriteName();
        phys_bank_manager->WriteLegalSubject(legal_subject);
        std::cout << "\n Write bithday date: ";
        phys_bank_manager->WriteBirthDayDate();
        std::cout << "\n Write address: ";
        phys_bank_manager->WriteAddress();
        std::cout << "\n Write passport: ";
        phys_bank_manager->WritePassport();

        PhysicalClient *new_client = phys_bank_manager->GetClient();

        WriteDataAboutClientToSQL(new_client, bank);
      }
    } else if (input == "open account") {
      std::cout << "\nwrite your name ";
      std::string name;
      std::getline(std::cin, name);
      std::string id_client = GetIdValueByName(name, bank);
      std::cout
          << "\nif you want to open a debit account, write debit, if you want to open a deposit account, write deposit, if you want to open a credit account, write credit. ";
      std::string operation;

      std::cin >> operation;
      if (operation == "debit") {
        ICreaterAccount *creater = new CreaterDebitAccount;
        IAccount *debit_account = creater->create();
        debit_account->CreateBankAccount(id_client, bank);

      } else if (operation == "deposit") {
        ICreaterAccount *creater = new CreaterDepositAccount;
        IAccount *deposit_account = creater->create();
        deposit_account->CreateBankAccount(id_client, bank);

      } else if (operation == "credit") {
        ICreaterAccount *creater = new CreaterCreditAccount;
        IAccount *cregit_account = creater->create();
        cregit_account->CreateBankAccount(id_client, bank);

      }

    } else if (input == "top up") {
      std::string condition = "NAME = '";
      std::cout << "\nwrite your name ";
      std::string name;
      std::getline(std::cin, name);
      condition += name + "'";
      std::string id_client = GetValueFromDatabase("test.db", "ID", bank, condition);
      std::cout
          << "\nif you want to top up a debit account, write debit, if you want to top up a deposit account, write deposit, if you want to take out a loan, write credit. ";
      std::string operation;
      std::cin >> operation;
      int amount;
      std::cout << "\nwrite amount ";
      if (operation == "debit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_DEBIT", condition);
        SqlCin(
            "UPDATE " + bank + "_DEBIT SET MONEY = '" + std::to_string(std::stoi(current) + amount) + "' WHERE ID = '"
                + id_client + "'");
      }
      if (operation == "deposit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_DEPOSIT", condition);
        SqlCin(
            "UPDATE " + bank + "_DEPOSIT SET MONEY = '" + std::to_string(std::stoi(current) + amount) + "' WHERE ID = '"
                + id_client + "'");
      }
      if (operation == "credit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_CREDIT", condition);
        SqlCin(
            "UPDATE " + bank + "_CREDIT SET MONEY = '" + std::to_string(std::stoi(current) + amount) + "' WHERE ID = '"
                + id_client + "'");
      }
    } else if (input == "withdraw") {
      std::cout << "\nwrite your name ";
      std::string condition = "NAME = '";
      std::string name;
      std::getline(std::cin, name);
      condition += name + "'";
      std::string id_client = GetValueFromDatabase("test.db", "ID", bank, condition);
      std::cout
          << "\nif you want to top up a debit account, write debit, if you want to top up a deposit account, write deposit, if you want to take out a loan, write credit. ";
      std::string operation;

      std::cin >> operation;
      int amount;
      std::cout << "\nwrite amount ";
      if (operation == "debit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_DEBIT", condition);
        SqlCin(
            "UPDATE " + bank + "_DEBIT SET MONEY = '" + std::to_string(std::stoi(current) - amount) + "' WHERE ID = '"
                + id_client + "'");
      }
      if (operation == "deposit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_DEPOSIT", condition);
        SqlCin(
            "UPDATE " + bank + "DEPOSIT SET MONEY = '" + std::to_string(std::stoi(current) - amount) + "' WHERE ID = '"
                + id_client + "'");
      }
      if (operation == "credit") {
        std::cin >> amount;
        condition = "ID = '" + id_client + "'";
        std::string current = GetValueFromDatabase("test.db", "MONEY", bank + "_CREDIT", condition);
        SqlCin(
            "UPDATE " + bank + "CREDIT SET MONEY = '" + std::to_string(std::stoi(current) - amount) + "' WHERE ID = '"
                + id_client + "'");
      }
    } else if (input == "close account") {
      std::cout << "\nwrite your name ";
      std::string condition = "NAME = '";
      std::string name;
      std::getline(std::cin, name);
      condition += name + "'";
      std::string id_client = GetValueFromDatabase("test.db", "ID", bank, condition);
      std::cout
          << "\nwhich account you want to close";
      std::string operation;
      std::cin >> operation;
      if (operation == "debit") {
        SqlCin("DELETE from " + bank + "_DEBIT where ID='" + id_client + "'");
        SqlCin("UPDATE SBERBANK SET DEBIT = 'NO' WHERE ID = '" + id_client + "'");
      }

      if (operation == "deposit") {
        SqlCin("DELETE from " + bank + "_DEPOSIT where ID='" + id_client + "'");
        SqlCin("UPDATE SBERBANK SET DEPOSIT = 'NO' WHERE ID = '" + id_client + "'");
      }

      if (operation == "credit") {
        SqlCin("DELETE from " + bank + "_CREDIT where ID='" + id_client + "'");
        SqlCin("UPDATE SBERBANK SET CREDIT = 'NO' WHERE ID = '" + id_client + "'");
      }

    } else if (input == "transfer money to another account in our bank") {//ok
      std::cout << "\nwrite your name ";
      std::string name_client;
      std::getline(std::cin, name_client);
      std::cout << "\ntransfer amount ";
      std::string amount;
      std::cin >> amount;
      std::cout << "\nwrite recipient's name ";
      std::string name_recipient;
      std::cin.ignore();
      std::getline(std::cin, name_recipient);
      InterbankTransfer(name_client, name_recipient, amount, bank, "YES");
    } else if (input == "cancel transaction within the bank") {//ok

      std::cout << "\nwrite your name ";
      std::string name_client;
      std::getline(std::cin, name_client);
      std::cout << "\ntransfer amount ";
      std::string amount;
      std::cin >> amount;
      std::cout << "\nwrite recipient's name ";
      std::string name_recipient;
      std::cin.ignore();
      std::getline(std::cin, name_recipient);
      InterbankTransfer(name_recipient, name_client, amount, bank, "NO");

    } else if (input == "transfer money to another account in other bank") {
      std::cout << "\nwrite your name ";
      std::string name_client;
      std::getline(std::cin, name_client);
      std::cout << "\ntransfer amount ";
      std::string amount;
      std::cin >> amount;
      std::cout << "\nwrite recipient's name ";
      std::string name_recipient;
      std::cin.ignore();
      std::getline(std::cin, name_recipient);
      std::cout << "\nwrite recipient's bank ";
      std::string bank_recipient;
      std::getline(std::cin, bank_recipient);
      TransferToAnotherBank(name_client, name_recipient, amount, bank, bank_recipient, "YES");
    } else if (input == "cancel transaction money to another account in other bank") {
      std::cout << "\nwrite your name ";
      std::string name_client;
      std::getline(std::cin, name_client);
      std::cout << "\ntransfer amount ";
      std::string amount;
      std::cin >> amount;
      std::cout << "\nwrite recipient's name ";
      std::string name_recipient;
      std::cin.ignore();
      std::getline(std::cin, name_recipient);
      std::cout << "\nwrite recipient's bank ";
      std::string bank_recipient;
      std::getline(std::cin, bank_recipient);
      TransferToAnotherBank(name_recipient, name_client, amount, bank_recipient, bank, "NO");
    }
    std::string session_continued;
    std::cout << "\nif you want to continue, write yes or no. ";
    std::cin >> session_continued;
    exit = (session_continued != "yes");
  }
}
