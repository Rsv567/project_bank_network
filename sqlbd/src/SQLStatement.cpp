#include "SQLStatement.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void SqlStatement(char *sql) {
  sqlite3 *db;
  char *zErrMsg = nullptr;
  int rc = sqlite3_open("h.db", &db);
  if(rc !=SQLITE_OK){
    std::cout<<"Невозможно открыть базу данных\n"<< sqlite3_errmsg(db);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
    return;
  }
  
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if(rc != SQLITE_OK){
    std::cout<<"Невозможно запустить statement"<<zErrMsg;
    }
  sqlite3_free(zErrMsg);
  sqlite3_close(db);
}
void SqlCin(std::string sql) {
  char *sql_cstr = new char[sql.length() + 1];
  std::strcpy(sql_cstr, sql.c_str());
  SqlStatement(sql_cstr);
}

std::string GetValueFromDatabase(const char *dbName,
                                 std::string fieldName,
                                 std::string tableName,
                                 std::string condition) {
  sqlite3 *db;
  char *errMsg = nullptr;
  int rc = sqlite3_open(dbName, &db); // Подключаемся к базе данных


  std::string value;

  std::string sql = "SELECT " + fieldName + "  FROM " + tableName + " WHERE " + condition + ";";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return "";
  }

  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    const char *result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)); // Получаем значение поля
    value = result;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db); // Закрываем соединение с базой данных

  return value;
}

