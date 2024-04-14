#include "bank_transfer.h"
#include "InputOutputData.h"
#include "SQLconst.h"

std::string GetIdValueByName(std::string name, std::string bank) {
  std::string condition = name;
  condition += name + "'";
  InputData *input_data = new SQLInput("ID", bank, condition);
  std::string data;
  input_data->input(data);
  return data;
}
std::string GetTheCurrentValueOfMoneyById(std::string id_client, std::string bank) {

  std::string condition = "ID = '" + id_client + "'";
  InputData *input_data = new SQLInput(money, bank + debit, condition);
  std::string data;
  input_data->input(data);
  return data;
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
  OutputData *sql_out = new SQLOutput;
  sql_out->output(update + bank + debit_set_money + current + where_id + id_client_decrease + "'");

  current = GetTheCurrentValueOfMoneyById(id_client_increase, bank);
  current = std::to_string(std::stoi(current) + std::stoi(amount));
  sql_out->output("UPDATE " + bank +debit_set_money + current + where_id + id_client_increase + "'");
  sql_out->output(
      insert_into + bank + "_OPERATIONS (ID_SENDER, ID_RECIPIENT, MONEY ) VALUES ('" + id_client_decrease + "', '"
          + id_client_increase + "' ,'" + amount + "');");
  if (is_trans == "NO") {
    sql_out->output(
        delete_from + bank + "_OPERATIONS where ID_Sender = '" + id_client_increase + "' AND ID_RECIPIENT = '"
            + id_client_decrease + "' AND MONEY = '" + amount + "'");
    sql_out->output(
        delete_from + bank + "_OPERATIONS where ID_Sender = '" + id_client_decrease + "' AND ID_RECIPIENT = '"
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
  OutputData *sql_out = new SQLOutput;
  InputData *sql_in = new SQLInput(money, "CENTRAL_BANK", "BANK = '" + bank_client_decrease + "'");
  std::string bank_client_money;
  sql_in->input(bank_client_money);
  sql_out->output(
      update + bank_client_decrease + debit_set_money + current + "' WHERE ID = '" + id_client_decrease
          + "'");
  sql_out->output("UPDATE CENTRAL_BANK SET MONEY = " + std::to_string(std::stoi(bank_client_money) - std::stoi(amount))
                      + " WHERE BANK = '" + bank_client_decrease + "'");

  sql_out->output(
      "INSERT INTO  CENTRAL_BANK_OPERATIONS (ID_SENDER, ID_RECIPIENT, BANK_SENDER, BANK_RECIPIENT,MONEY ) VALUES ('"
          + id_client_decrease + "', '"
          + id_client_increase + "' ,'" + bank_client_decrease + "' ,'" + bank_client_increase + "' ,'" + amount
          + "');");
  InputData *sql_in2 = new SQLInput(money, "CENTRAL_BANK", "BANK = '" + bank_client_increase + "'");

  std::string bank_recipient_money;
  sql_in2->input(bank_recipient_money);
  sql_out->output(
      "UPDATE CENTRAL_BANK SET MONEY = " + std::to_string(std::stoi(bank_recipient_money) + std::stoi(amount))
          + " WHERE BANK = '" + bank_client_increase + "'");
  current = GetTheCurrentValueOfMoneyById(id_client_increase, bank_client_increase);
  current = std::to_string(std::stoi(current) + std::stoi(amount));
  sql_out->output(
      update + bank_client_increase + debit_set_money + current + "' WHERE ID = '" + id_client_increase
          + "'");
  if (is_trans == "NO") {
    sql_out->output(
        "DELETE from CENTRAL_BANK_OPERATIONS WHERE ID_SENDER = '" + id_client_decrease + "' AND ID_RECIPIENT = '"
            + id_client_increase + "' AND MONEY = '" + amount + "'");
    sql_out->output(
        "DELETE from CENTRAL_BANK_OPERATIONS WHERE ID_SENDER = '" + id_client_increase + "' AND ID_RECIPIENT = '"
            + id_client_decrease + "' AND MONEY = '" + amount + "'");
  }
}