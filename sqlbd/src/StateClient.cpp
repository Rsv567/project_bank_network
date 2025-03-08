#include "StateClient.h"

void RegistrationState::Input(std::string bank) {
  std::string is_legal;
  std::string legal_subject = "legal person";
  InputData *out_data = new GraphicsInput("legal");

  out_data->input(is_legal);

  if (legal_subject == is_legal) {
    IBankManager *phys_bank_manager = new CreaterPhysicalPerson;
    phys_bank_manager->WriteName();
    phys_bank_manager->WriteLegalSubject(legal_subject);
    phys_bank_manager->WriteBirthDayDate();

    phys_bank_manager->WriteAddress();

    phys_bank_manager->WritePassport();

    PhysicalClient *new_client = phys_bank_manager->GetClient();

    WriteDataAboutClientToSQL(new_client, bank);
  }
}
void OpenAccountState::Input(std::string bank) {

  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  std::string name;
  out_data->input(name);
  std::string id_client = GetIdValueByName(name, bank);
  std::cout << id_client;
  std::unique_ptr<InputData> out_datax(new GraphicsInput("open_account"));
  std::string operation;

  out_datax->input(operation);
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
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  std::string condition = name;

  std::string names;
  out_data->input(names);
  condition += names + "'";
  InputData *sql_data = new SQLInput("ID", bank, condition);
  std::string id_client;
  sql_data->input(id_client);

  std::unique_ptr<InputData> out_datax(new GraphicsInput("top_up"));

  std::string operation;
  out_datax->input(operation);
  std::string amount;
  std::unique_ptr<InputData> out_datas(new GraphicsInput("write_amount"));
  out_datas->input(amount);
  if (operation == "debit") {
    condition = "ID = '" + id_client + "'";

    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + debit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + debit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "deposit") {

    condition = "ID = '" + id_client + "'";
    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + deposit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + deposit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "credit") {

    condition = "ID = '" + id_client + "'";
    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + credit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + credit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
            + where_id
            + id_client + "'");
  }
}

void WithdrawState::Input(std::string bank) {

  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  std::string condition = name;

  std::string names;
  out_data->input(names);
  condition += names + "'";
  InputData *sql_data = new SQLInput("ID", bank, condition);
  std::string id_client;
  sql_data->input(id_client);

  std::unique_ptr<InputData> out_datax(new GraphicsInput("withdraw"));

  std::string operation;
  out_datax->input(operation);
  std::string amount;
  std::unique_ptr<InputData> out_datas(new GraphicsInput("write_amount"));
  out_datas->input(amount);
  if (operation == "debit") {
    condition = "ID = '" + id_client + "'";

    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + debit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + debit_set_money + std::to_string(std::stoi(current) - std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "deposit") {

    condition = "ID = '" + id_client + "'";
    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + deposit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + deposit_set_money + std::to_string(std::stoi(current) - std::stoi(amount))
            + "' WHERE ID = '"
            + id_client + "'");
  }
  if (operation == "credit") {

    condition = "ID = '" + id_client + "'";
    std::unique_ptr<InputData> cin_data(new SQLInput(money, bank + credit, condition));
    std::string current;
    cin_data->input(current);
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output(
        update + bank + credit_set_money + std::to_string(std::stoi(current) - std::stoi(amount))
            + where_id
            + id_client + "'");
  }

}

void CloseState::Input(std::string bank) {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));

  std::string condition = name;
  std::string names;
  out_data->input(names);
  condition += name + "'";

  std::unique_ptr<InputData> cin_data ( new SQLInput("ID", bank, condition));

  std::string id_client;
  cin_data->input(id_client);
  std::unique_ptr<InputData> out_datas(new GraphicsInput("close"));


  std::string operation;
  out_datas->input(operation);
  if (operation == "debit") {
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output("DELETE from " + bank + "_DEBIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET DEBIT = 'NO' WHERE ID = '" + id_client + "'");
  }

  if (operation == "deposit") {
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output("DELETE from " + bank + "_DEPOSIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET DEPOSIT = 'NO' WHERE ID = '" + id_client + "'");
  }

  if (operation == "credit") {
    std::unique_ptr<OutputData> cout_data(new SQLOutput);
    cout_data->output("DELETE from " + bank + "_CREDIT where ID='" + id_client + "'");
    cout_data->output(update + bank + " SET CREDIT = 'NO' WHERE ID = '" + id_client + "'");
  }
}
void TransferAnotherBankState::Input(std::string bank) {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));

  std::string name_client;
  out_data->input(name_client);
  std::unique_ptr<InputData> out_datax(new GraphicsInput("transfer_amount"));
  std::string amount;
  out_datax->input(amount);
  std::unique_ptr<InputData> out_datas(new GraphicsInput("name_re"));
  std::string name_recipient;
  out_datas->input(name_recipient);
  std::unique_ptr<InputData> out_datac(new GraphicsInput("bank_r"));
  std::string bank_recipient;
  out_datac->input(bank_recipient);

  TransferToAnotherBank(name_client, name_recipient, amount, bank, bank_recipient, "YES");
}

void TransactionWithinBankState::Input(std::string bank) {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  std::string name_client;
  out_data->input(name_client);
  std::unique_ptr<InputData> out_datax(new GraphicsInput("transfer_amount"));
  std::string amount;
  out_datax->input(amount);
  std::unique_ptr<InputData> out_datas(new GraphicsInput("name_re"));
  std::string name_recipient;
  out_datas->input(name_recipient);
  InterbankTransfer(name_client, name_recipient, amount, bank, "YES");
}

void CanselTransactionWithinBankState::Input(std::string bank) {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  std::string name_client;
  out_data->input(name_client);
  std::unique_ptr<InputData> out_datax(new GraphicsInput("transfer_amount"));
  std::string amount;
  out_datax->input(amount);
  std::unique_ptr<InputData> out_datas(new GraphicsInput("name_re"));
  std::string name_recipient;
  out_datas->input(name_recipient);
  InterbankTransfer(name_recipient, name_client, amount, bank, "NO");
}

void CanselTransactionAnotherBankState::Input(std::string bank) {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));

  std::string name_client;
  out_data->input(name_client);
  std::unique_ptr<InputData> out_datax(new GraphicsInput("transfer_amount"));
  std::string amount;
  out_datax->input(amount);
  std::unique_ptr<InputData> out_datas(new GraphicsInput("name_re"));
  std::string name_recipient;
  out_datas->input(name_recipient);
  std::unique_ptr<InputData> out_datac(new GraphicsInput("bank_r"));
  std::string bank_recipient;
  out_datac->input(bank_recipient);
  TransferToAnotherBank(name_recipient, name_client, amount, bank_recipient, bank, "NO");
}