#include"AccountOpening.h"

void DebitAccount::CreateBankAccount(std::string id_client, std::string bank) {
  std::string sql = "INSERT INTO " + bank + "_DEBIT (ID, MONEY )" \
  " VALUES ('" + id_client + "',0); ";
  char *sql_cstr = new char[sql.length() + 1];
  std::strcpy(sql_cstr, sql.c_str());
  SqlStatement(sql_cstr);
  std::string sql2 = "UPDATE " + bank + " SET DEBIT = 'YES' WHERE ID = " + id_client;
  char *sql2_cstr = new char[sql2.length() + 1];
  std::strcpy(sql2_cstr, sql2.c_str());
  SqlStatement(sql2_cstr);

}

void DepositAccount::CreateBankAccount(std::string id_client, std::string bank) {
  std::string sql = "INSERT INTO " + bank + "_DEPOSIT (ID, MONEY, PERCENTS )" \
  " VALUES ('" + id_client + "',0, 5.2); ";
  char *sql_cstr = new char[sql.length() + 1];
  std::strcpy(sql_cstr, sql.c_str());
  SqlStatement(sql_cstr);
  std::string sql2 = "UPDATE " + bank + " SET DEPOSIT = 'YES' WHERE ID = " + id_client;
  char *sql2_cstr = new char[sql2.length() + 1];
  std::strcpy(sql2_cstr, sql2.c_str());
  SqlStatement(sql2_cstr);
}

void CreditAccount::CreateBankAccount(std::string id_client, std::string bank) {
  std::string sql = "INSERT INTO " + bank + "_CREDIT (ID, MONEY, PERCENTS )" \
  " VALUES ('" + id_client + "',0,5.2); ";
  char *sql_cstr = new char[sql.length() + 1];
  std::strcpy(sql_cstr, sql.c_str());
  SqlStatement(sql_cstr);
  std::string sql2 = "UPDATE " + bank + " SET CREDIT = 'YES' WHERE ID = " + id_client;
  char *sql2_cstr = new char[sql2.length() + 1];
  std::strcpy(sql2_cstr, sql2.c_str());
  SqlStatement(sql2_cstr);
}

IAccount *CreaterDebitAccount::create() {
  return new DebitAccount;
}

IAccount *CreaterDepositAccount::create() {
  return new DepositAccount;
}

IAccount *CreaterCreditAccount::create() {
  return new CreditAccount;
}
