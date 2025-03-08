//
// Created by rsv567 on 01.04.24.
//

#ifndef SQLBD__SQLCONST_H_
#define SQLBD__SQLCONST_H_
#include <string>
static std::string update = "UPDATE ";
static std::string debit_set_money = "_DEBIT SET MONEY = '";
static std::string where_id = "' WHERE ID = '";
static std::string deposit_set_money = "_DEPOSIT SET MONEY = '";
static std::string credit_set_money = "_CREDIT SET MONEY = '";
static std::string id = "ID = '";
static std::string name = "NAME = '";
static std::string delete_from = "DELETE from ";
static std::string debit_where_id = "_DEBIT where ID='";
static std::string deposit_where_id = "_DEPOSIT where ID='";
static std::string credit_where_id = "_CREDIT where ID='";
static std::string money = "MONEY";
static std::string debit = "_DEBIT";
static std::string deposit = "_DEPOSIT";
static std::string credit = "_CREDIT";
static std::string insert_into = "INSERT INTO ";
static std::string values = " VALUES ('";
#endif //SQLBD__SQLCONST_H_
