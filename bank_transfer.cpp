#include "bank_transfer.h"
std::string GetIdValueByName(std::string name, std::string bank) {
  std::string condition = "NAME = '";
  condition += name + "'";
  return GetValueFromDatabase("test.db", "ID", bank, condition);
}
std::string GetTheCurrentValueOfMoneyById(std::string id_client, std::string bank) {
  std::string condition = "ID = '" + id_client + "'";
  return GetValueFromDatabase("test.db", "MONEY", bank + "_DEBIT", condition);
}
void InterbankTransfer(std::string name_decrease,
                       std::string name_increase,
                       std::string amount,
                       std::string bank,
                       std::string is_trans) {

  std::string id_client_decrease = GetIdValueByName(name_decrease, bank);
  std::string id_client_increase = GetIdValueByName(name_increase, bank);
  std::string current = GetTheCurrentValueOfMoneyById(id_client_decrease, bank);
  current = std::to_string(std::stoi(current) - std::stoi(amount));
  SqlCin("UPDATE " + bank + "_DEBIT SET MONEY = '" + current + "' WHERE ID = '" + id_client_decrease + "'");

  current = GetTheCurrentValueOfMoneyById(id_client_increase, bank);
  current = std::to_string(std::stoi(current) + std::stoi(amount));
  SqlCin("UPDATE " + bank + "_DEBIT SET MONEY = '" + current + "' WHERE ID = '" + id_client_increase + "'");
  SqlCin(
      "INSERT INTO " + bank + "_OPERATIONS (ID_SENDER, ID_RECIPIENT, MONEY ) VALUES ('" + id_client_decrease + "', '"
          + id_client_increase + "' ,'" + amount + "');");
  if (is_trans == "NO") {
    SqlCin("DELETE from " + bank + "_OPERATIONS where ID_Sender = '" + id_client_increase + "' AND ID_RECIPIENT = '"
               + id_client_decrease + "' AND MONEY = '" + amount + "'");
    SqlCin("DELETE from " + bank + "_OPERATIONS where ID_Sender = '" + id_client_decrease + "' AND ID_RECIPIENT = '"
               + id_client_increase + "' AND MONEY = '" + amount + "'");
  }

}

void TransferToAnotherBank(std::string name_client_decrease,
                           std::string name_client_increase,
                           std::string amount,
                           std::string bank_client_decrease,
                           std::string bank_client_increase,
                           std::string is_trans) {
  std::string id_client_decrease = GetIdValueByName(name_client_decrease, bank_client_decrease);
  std::string id_client_increase = GetIdValueByName(name_client_increase, bank_client_increase);
  std::string current = GetTheCurrentValueOfMoneyById(id_client_decrease, bank_client_decrease);
  current = std::to_string(std::stoi(current) - std::stoi(amount));
  std::string bank_client_money =
      GetValueFromDatabase("test.db", "MONEY", "CENTRAL_BANK", "BANK = '" + bank_client_decrease + "'");
  SqlCin("UPDATE " + bank_client_decrease + "_DEBIT SET MONEY = '" + current + "' WHERE ID = '" + id_client_decrease
             + "'");
  SqlCin("UPDATE CENTRAL_BANK SET MONEY = " + std::to_string(std::stoi(bank_client_money) - std::stoi(amount))
             + " WHERE BANK = '" + bank_client_decrease + "'");

  SqlCin("INSERT INTO  CENTRAL_BANK_OPERATIONS (ID_SENDER, ID_RECIPIENT, BANK_SENDER, BANK_RECIPIENT,MONEY ) VALUES ('"
             + id_client_decrease + "', '"
             + id_client_increase + "' ,'" + bank_client_decrease + "' ,'" + bank_client_increase + "' ,'" + amount
             + "');");

  std::string bank_recipient_money =
      GetValueFromDatabase("test.db", "MONEY", "CENTRAL_BANK", "BANK = '" + bank_client_increase + "'");
  SqlCin("UPDATE CENTRAL_BANK SET MONEY = " + std::to_string(std::stoi(bank_recipient_money) + std::stoi(amount))
             + " WHERE BANK = '" + bank_client_increase + "'");
  current = GetTheCurrentValueOfMoneyById(id_client_increase, bank_client_increase);
  current = std::to_string(std::stoi(current) + std::stoi(amount));
  SqlCin("UPDATE " + bank_client_increase + "_DEBIT SET MONEY = '" + current + "' WHERE ID = '" + id_client_increase
             + "'");
  if (is_trans == "NO") {
    SqlCin("DELETE from CENTRAL_BANK_OPERATIONS WHERE ID_SENDER = '" + id_client_decrease + "' AND ID_RECIPIENT = '"
               + id_client_increase + "' AND MONEY = '" + amount + "'");
    SqlCin("DELETE from CENTRAL_BANK_OPERATIONS WHERE ID_SENDER = '" + id_client_increase + "' AND ID_RECIPIENT = '"
               + id_client_decrease + "' AND MONEY = '" + amount + "'");
  }
}