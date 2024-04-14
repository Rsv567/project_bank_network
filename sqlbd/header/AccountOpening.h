#ifndef SQLBD__ACCOUNTOPENING_H_
#define SQLBD__ACCOUNTOPENING_H_
#include "SQLStatement.h"
#include "InputOutputData.h"
#include "SQLconst.h"

class IAccount {
 public:
  virtual void CreateBankAccount(std::string id_client, std::string bank) = 0;
};
class DebitAccount : public IAccount {
 public:
  void CreateBankAccount(std::string id_client, std::string bank) override;
};

class DepositAccount : public IAccount {
 public:
  void CreateBankAccount(std::string id_client, std::string bank) override;
};
class CreditAccount : public IAccount {
  void CreateBankAccount(std::string id_client, std::string bank) override;
};

class ICreaterAccount {
 public:
  virtual IAccount *create() = 0;
};

class CreaterDebitAccountSQL : public ICreaterAccount {
  IAccount *create() override;
};

class CreaterDepositAccountSQL : public ICreaterAccount {
  IAccount *create() override;
};

class CreaterCreditAccountSQL : public ICreaterAccount {
  IAccount *create() override;
};

#endif //SQLBD__ACCOUNTOPENING_H_
