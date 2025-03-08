#include <gtest/gtest.h>

#include "../header/StateClient.h"

#include "../header/create_data_base.h"

TEST(Test1, id) {
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("10001212345678", "ann","legal subject", "13.02.1990", "Moscow", "12345678","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string id = GetValueFromDatabase("test.db","ID", "SBERBANK", "NAME = 'ann'");

  ASSERT_EQ(id, "10001212345678");

  delete client;
}
TEST(Test1, name){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567", "sam smit","legal subject", "13.02.1990", "Moscow", "1234567","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string name = GetValueFromDatabase("test.db","NAME", "SBERBANK", "ID = '1000121234567'");
  ASSERT_EQ(name, "sam smit");
  delete client;
}
TEST(Test1, birthday){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("100012123456", "Anna","legal subject", "13.02.1990", "Moscow", "123456","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string birthday = GetValueFromDatabase("test.db","BIRTHDAY", "SBERBANK", "ID = '100012123456'");

  ASSERT_EQ(birthday, "13.02.1990");
  delete client;
}

TEST(Test1, legal){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("10001212345", "ann","legal subject", "13.02.1990", "Moscow MIPT", "12345","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string legal = GetValueFromDatabase("test.db","LEGALSUBJECT", "SBERBANK", "ID = '10001212345'");

  ASSERT_EQ(legal, "legal subject");
  delete client;
}
TEST(Test1, address){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234", "ann","legal subject", "13.02.199034", "Moscow HSE", "1234","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string address = GetValueFromDatabase("test.db","ADDRESS", "SBERBANK", "ID = '1000121234'");

  ASSERT_EQ(address, "Moscow HSE");
  delete client;
}

TEST(Test1, passport){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("100012123", "ann","legal subject", "13.02.1990", "Moscow", "123","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string passport= GetValueFromDatabase("test.db","PASSPORT", "SBERBANK", "ID = '100012123'");

  ASSERT_EQ(passport, "123");
  delete client;
}

TEST(Test1, debit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("100012123456789", "qwerty yuiu e","legal subject", "13.02.1990", "Moscow", "123456789","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  std::string debit = GetValueFromDatabase("test.db","DEBIT", "SBERBANK", "ID = '100012123456789'");

  ASSERT_EQ(debit, "NO");
  delete client;
}
TEST(Test1, deposit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567810", "ann","legal subject", "13.02.1990", "Moscow", "1234567810","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");

  std::string deposit = GetValueFromDatabase("test.db","DEPOSIT", "SBERBANK", "ID = '1000121234567810'");

  ASSERT_EQ(deposit, "NO");
  delete client;
}

TEST(Test1, credit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567811", "ann","legal subject", "13.02.1990", "Moscow", "1234567811","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");

  std::string credit = GetValueFromDatabase("test.db","CREDIT", "SBERBANK", "ID = '1000121234567811'");

  ASSERT_EQ(credit, "NO");
  delete client;
}
TEST(Test2, debit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567812", "Ryazanov Svyatoslav ","legal subject", "13.02.2001", "Moscow", "1234567812","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  ICreaterAccount *creater = new CreaterDebitAccountSQL;
  IAccount *debit_account = creater->create();
  debit_account->CreateBankAccount("1000121234567812", "SBERBANK");
  std::string debit = GetValueFromDatabase("test.db","DEBIT", "SBERBANK", "ID = '1000121234567812'");
  ASSERT_EQ(debit, "YES");
}

TEST(Test2, deposit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567813", "Ryazanov Svyatoslav Victory ","legal subject", "13.02.2001", "Moscow", "1234567813","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  ICreaterAccount *creater = new CreaterDebitAccountSQL;
  IAccount *debit_account = creater->create();
  debit_account->CreateBankAccount("1000121234567813", "SBERBANK");
  std::string debit = GetValueFromDatabase("test.db","DEBIT", "SBERBANK", "ID = '1000121234567813'");
  ASSERT_EQ(debit, "YES");
  delete client;
}

TEST(Test2, credit){
  CreateDataBase();
  PhysicalClient* client = new PhysicalClient("1000121234567814", "Vladimir Yurchenco","legal subject", "13.02.2001", "Moscow", "1234567814","NO","NO","NO");
  WriteDataAboutClientToSQL(client,"SBERBANK");
  ICreaterAccount *creater = new CreaterDebitAccountSQL;
  IAccount *debit_account = creater->create();
  debit_account->CreateBankAccount("1000121234567814", "SBERBANK");
  std::string debit = GetValueFromDatabase("test.db","DEBIT", "SBERBANK", "ID = '1000121234567814'");
  ASSERT_EQ(debit, "YES");
  delete client;
}

TEST(Test3, transfer){
  CreateDataBase();
  std::string bank = "SBERBANK";
  std::string id_client1 = "1000121234567816";
  std::string id_client2 = "1000121234567815";
  PhysicalClient* client1 = new PhysicalClient(id_client1, "X","legal subject", "13.02.2001", "Moscow", "1234567816","NO","NO","NO");
  WriteDataAboutClientToSQL(client1,bank);
  PhysicalClient* client2 = new PhysicalClient(id_client2, "Y","legal subject", "13.02.2001", "Moscow", "1234567815","NO","NO","NO");
  WriteDataAboutClientToSQL(client2,bank);

  ICreaterAccount *creater1 = new CreaterDebitAccountSQL;
  IAccount *debit_account1 = creater1->create();
  debit_account1->CreateBankAccount("1000121234567816", "SBERBANK");

  ICreaterAccount *creater2 = new CreaterDebitAccountSQL;
  IAccount *debit_account2 = creater2->create();
  debit_account2->CreateBankAccount("1000121234567815", "SBERBANK");

  std::string amount = "100";
  std::string condition = "ID = '1000121234567816'";
  std::unique_ptr<InputData> cin_data(new SQLInput(money, "SBERBANK_DEBIT", condition));
  std::string current;
  cin_data->input(current);
  std::unique_ptr<OutputData> cout_data(new SQLOutput);
  cout_data->output(
      update + bank + debit_set_money + std::to_string(std::stoi(current) + std::stoi(amount))
          + "' WHERE ID = '"
          + id_client1 + "'");

  std::string real_amount = GetValueFromDatabase("test.db","MONEY", "SBERBANK_DEBIT", "ID = '1000121234567816'");
  ASSERT_EQ(real_amount,"100");

  std::string condition2 = "ID = '1000121234567815'";
  std::unique_ptr<InputData> cin_data2(new SQLInput(money, "SBERBANK_DEBIT", condition2));
  std::string current2;
  cin_data2->input(current2);
  std::unique_ptr<OutputData> cout_data2(new SQLOutput);
  cout_data2->output(
      update + bank + debit_set_money + std::to_string(std::stoi(current2) + std::stoi(amount))
          + "' WHERE ID = '"
          + id_client2 + "'");

  std::string real_amount2 = GetValueFromDatabase("test.db","MONEY", "SBERBANK_DEBIT", "ID = '1000121234567815'");
  ASSERT_EQ(real_amount2,"100");

  InterbankTransfer("X","Y",amount,"SBERBANK","YES");

  std::string inter_amount1 = GetValueFromDatabase("test.db","MONEY", "SBERBANK_DEBIT", "ID = '1000121234567816'");
  std::string inter_amount2 = GetValueFromDatabase("test.db","MONEY", "SBERBANK_DEBIT", "ID = '1000121234567815'");
  ASSERT_EQ(inter_amount1,"0");
  ASSERT_EQ(inter_amount2,"200");
}

