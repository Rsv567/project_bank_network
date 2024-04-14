#include "StateClient.h"

void RegistrationState::Input(std::string bank) {
  std::string is_legal;
  std::string legal_subject = "legal person";
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;
  cout_data->output("write down which legal entity you are: ");
  cin_data->input(is_legal);

  if (legal_subject == is_legal) {
    IBankManager *phys_bank_manager = new CreaterPhysicalPerson;
    cout_data->output("\n Write name: ");
    phys_bank_manager->WriteName();
    phys_bank_manager->WriteLegalSubject(legal_subject);
    cout_data->output("\n Write bithday date: ");
    phys_bank_manager->WriteBirthDayDate();
    cout_data->output("\n Write address: ");
    phys_bank_manager->WriteAddress();
    cout_data->output("\n Write passport: ");
    phys_bank_manager->WritePassport();

    PhysicalClient *new_client = phys_bank_manager->GetClient();

    WriteDataAboutClientToSQL(new_client, bank);
  }
}
void OpenAccountState::Input(std::string bank) {
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;
  cout_data->output("\nwrite your name ");
  std::string name;
  cin_data->input(name);
  std::string id_client = GetIdValueByName(name, bank);
  cout_data->output(
      "\nif you want to open a debit account, write debit, if you want to open a deposit account, write deposit, if you want to open a credit account, write credit. ");
  std::string operation;

  cin_data->input(operation);
  if (operation == "debit") {
    ICreaterAccount *creater = new CreaterDebitAccountSQL;
    IAccount *debit_account = creater->create();
    debit_account->CreateBankAccount(id_client, bank);

  } else if (operation == "deposit") {
    ICreaterAccount *creater = new CreaterDepositAccountSQL;
    IAccount *deposit_account = creater->create();
    deposit_account->CreateBankAccount(id_client, bank);

  } else if (operation == "credit") {
    ICreaterAccount *creater = new CreaterCreditAccountSQL;
    IAccount *cregit_account = creater->create();
    cregit_account->CreateBankAccount(id_client, bank);

  }

}

void TopUpState::Input(std::string bank) {
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;

  std::string condition = name;
  cout_data->output("\nwrite your name ");
  std::string name;
  cin_data->input(name);
  condition += name + "'";
  cin_data = new SQLInput("ID", bank, condition);
  std::string id_client;
  cin_data->input(id_client);
  cout_data->output(
      "\nif you want to top up a debit account, write debit, if you want to top up a deposit account, write deposit, if you want to take out a loan, write credit. ");
  std::string operation;
  cin_data = new ConsoleInput;
  cin_data->input(operation);
  std::string amount;
  cout_data->output("\nwrite amount ");
  if (operation == "debit") {
    cin_data->input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + debit, condition);
    std::string current;
    cin_data->input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + debit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "deposit") {
    cin_data->input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + deposit, condition);
    std::string current;
    cin_data->input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + deposit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "credit") {
    cin_data->input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + credit, condition);
    std::string current;
    cin_data->input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + credit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + where_id
            + id_client + "'");
  }
}

void WithdrawState::Input(std::string bank) {
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;

  cout_data->output("\nwrite your name ");
  std::string condition = name;
  std::string name;
  cin_data->
      input(name);
  condition += name + "'";

  cin_data = new SQLInput("ID", bank, condition);

  std::string id_client;
  cin_data->
      input(id_client);
  cout_data->output(
      "\nif you want to withdraw a debit account, write debit, if you want to withdraw a deposit account, write deposit, if you want to take out a loan, write credit. ");
  std::string operation;
  cin_data = new ConsoleInput;
  cin_data->
      input(operation);
  std::string amount;
  cout_data->output("\nwrite amount ");
  if (operation == "debit") {
    cin_data->
        input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + debit, condition);
    std::string current;
    cin_data->
        input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + debit_set_money +
            std::to_string(std::stoi(current)
                               -
                                   std::stoi(amount)
            )
            + where_id
            + id_client + "'");
  }
  if (operation == "deposit") {
    cin_data->
        input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + deposit, condition);
    std::string current;
    cin_data->
        input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + deposit_set_money +
            std::to_string(std::stoi(current)
                               -
                                   std::stoi(amount)
            )
            + where_id
            + id_client + "'");
  }
  if (operation == "credit") {
    cin_data->
        input(amount);
    condition = "ID = '" + id_client + "'";
    cin_data = new SQLInput(money, bank + credit, condition);
    std::string current;
    cin_data->
        input(current);
    cout_data = new SQLOutput;
    cout_data->output(
        update + bank + credit_set_money +
            std::to_string(std::stoi(current)
                               -
                                   std::stoi(amount)
            )
            + where_id
            + id_client + "'");
  }
}

void CloseState::Input(std::string bank) {
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;
  cout_data->output("\nwrite your name ");
  std::string condition = name;
  std::string name;
  cin_data->input(name);
  condition += name + "'";

  cin_data = new SQLInput("ID", bank, condition);

  std::string id_client;
  cin_data->input(id_client);

  cout_data->output("\nwhich account you want to close");
  cin_data = new ConsoleInput;
  std::string operation;
  cin_data->input(operation);
  if (operation == "debit") {
    cout_data = new SQLOutput;
    cout_data->output("DELETE from " + bank + "_DEBIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET DEBIT = 'NO' WHERE ID = '" + id_client + "'");
  }

  if (operation == "deposit") {
    cout_data = new SQLOutput;
    cout_data->output("DELETE from " + bank + "_DEPOSIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET DEPOSIT = 'NO' WHERE ID = '" + id_client + "'");
  }

  if (operation == "credit") {
    cout_data = new SQLOutput;
    cout_data->output("DELETE from " + bank + "_CREDIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET CREDIT = 'NO' WHERE ID = '" + id_client + "'");
  }
}

void TransferAnotherBankState::Input(std::string bank) {
  InputData *cin_data = new ConsoleInput;
  OutputData *cout_data = new ConsoleOutput;
  cout_data->output("\nwrite your name ");
  std::string name_client;
  cin_data->input(name_client);
  cout_data->output("\ntransfer amount ");
  std::string amount;
  cin_data->input(amount);
  cout_data->output("\nwrite recipient's name ");
  std::string name_recipient;
  cin_data->input(name_recipient);
  cout_data->output("\nwrite recipient's bank ");
  std::string bank_recipient;
  cin_data->input(bank_recipient);
  TransferToAnotherBank(name_client, name_recipient, amount, bank, bank_recipient, "YES");
}

void TransactionWithinBankState::Input(std::string bank) {
  InputData *cin_data = new ConsoleInput;
  OutputData *cout_data = new ConsoleOutput;
  cout_data->output("\nwrite your name ");
  std::string name_client;
  cin_data->input(name_client);
  cout_data->output("\ntransfer amount ");
  std::string amount;
  cin_data->input(amount);
  cout_data->output("\nwrite recipient's name ");
  std::string name_recipient;
  cin_data->input(name_recipient);
  InterbankTransfer(name_client, name_recipient, amount, bank, "YES");
}

void CanselTransactionWithinBankState::Input(std::string bank) {
  InputData *cin_data = new ConsoleInput;
  OutputData *cout_data = new ConsoleOutput;
  cout_data->output("\nwrite your name ");
  std::string name_client;
  cin_data->input(name_client);
  cout_data->output("\ntransfer amount ");
  std::string amount;
  cin_data->input(amount);
  cout_data->output("\nwrite recipient's name ");
  std::string name_recipient;

  cin_data->input(name_recipient);
  InterbankTransfer(name_recipient, name_client, amount, bank, "NO");
}

void CanselTransactionAnotherBankState::Input(std::string bank) {
  OutputData *cout_data = new ConsoleOutput;
  InputData *cin_data = new ConsoleInput;
  cout_data->output("\nwrite your name ");
  std::string name_client;
  cin_data->input(name_client);
  cout_data->output("\ntransfer amount ");
  std::string amount;
  cin_data->input(amount);
  cout_data->output("\nwrite recipient's name ");
  std::string name_recipient;
  cin_data->input(name_recipient);
  cout_data->output("\nwrite recipient's bank ");
  std::string bank_recipient;
  cin_data->input(bank_recipient);
  TransferToAnotherBank(name_recipient, name_client, amount, bank_recipient, bank, "NO");
}