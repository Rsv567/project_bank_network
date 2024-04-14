#include"AccountOpening.h"


void DebitAccount::CreateBankAccount(std::string id_client, std::string bank) {
  OutputData *cout_data = new SQLOutput;

  std::string sql = insert_into + bank + "_DEBIT (ID, MONEY )" +
  values + id_client + "',0); ";
  cout_data->output(sql);
  std::string sql2 = update + bank + " SET DEBIT = 'YES' WHERE ID = '" + id_client + "'";
  cout_data->output(sql2);
}

void DepositAccount::CreateBankAccount(std::string id_client, std::string bank) {
  OutputData *cout_data = new SQLOutput;
  std::string sql = insert_into + bank + "_DEPOSIT (ID, MONEY, PERCENTS )" +
  values + id_client + "',0, 5.2); ";
  cout_data->output(sql);
  std::string sql2 = update + bank + " SET DEPOSIT = 'YES' WHERE ID = '" + id_client + "'";
  cout_data->output(sql2);
}

void CreditAccount::CreateBankAccount(std::string id_client, std::string bank) {
  OutputData *cout_data = new SQLOutput;
  std::string sql = insert_into+ bank + "_CREDIT (ID, MONEY, PERCENTS )" +
  values + id_client + "',0,5.2); ";
  cout_data->output(sql);
  std::string sql2 = update + bank + " SET CREDIT = 'YES' WHERE ID = '" + id_client + "'";
  cout_data->output(sql2);
}

IAccount *CreaterDebitAccountSQL::create() {
  return new DebitAccount;
}

IAccount *CreaterDepositAccountSQL::create() {
  return new DepositAccount;
}

IAccount *CreaterCreditAccountSQL::create() {
  return new CreditAccount;
}
