#ifndef SQLBD__INPUTOUTPUTDATA_H_
#define SQLBD__INPUTOUTPUTDATA_H_
#include <string>
#include <iostream>
#include "SQLStatement.h"

class InputData {
 public:
  virtual void input(std::string &query) = 0;

};

class OutputData {
 public:
  virtual void output(std::string query) = 0;
};
/////////////////////////////////////////////
class SQLOutput : public OutputData {
 public:
  void output(std::string query) override {
    SqlCin(query);
  }
};

class ConsoleOutput : public OutputData {
 public:
  void output(std::string query) override {
    std::cout << query;
  }
};
////////////////////////////////////////////
class ConsoleInput : public InputData {
 public:
  void input(std::string &query) override {
    std::getline(std::cin, query);
  }
};
class SQLInput : public InputData {
 private:
  std::string fieldName_;
  std::string bank_;
  std::string condition_;
 public:
  SQLInput(std::string fieldName, std::string bank, std::string condition)
      : fieldName_(fieldName), bank_(bank), condition_(condition) {}
  void input(std::string &query) override {
    query = GetValueFromDatabase("test.db", fieldName_, bank_, condition_);
  }
};
#endif //SQLBD__INPUTOUTPUTDATA_H_
