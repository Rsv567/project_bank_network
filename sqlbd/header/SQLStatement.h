//
// Created by rsv567 on 05.03.24.
//

#ifndef SQLBD__SQLSTATEMENT_H_
#define SQLBD__SQLSTATEMENT_H_
#include "../libraries/sqlite3.h"
#include <string>
#include <iostream>
#include<cstring>
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void SqlStatement(char *sql);
void SqlCin(std::string sql);
std::string GetValueFromDatabase(const char *dbName,
                                 std::string fieldName,
                                 std::string tableName,
                                 std::string condition);
#endif //SQLBD__SQLSTATEMENT_H_
