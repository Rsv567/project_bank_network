#ifndef SQLBD__REGISTRATION_H_
#define SQLBD__REGISTRATION_H_
#include <cstring>
#include "SQLStatement.h"
#include "Registration.h"
class CreaterPhysicalPerson;
class PhysicalClient {
 private:
  std::string id;
  std::string name;
  std::string legal_subject;
  std::string birthday_date;
  std::string address;
  std::string passport;
  std::string debit;
  std::string deposit;
  std::string credit;

 public:
  PhysicalClient();
  PhysicalClient(std::string id,
                 std::string name_,
                 std::string legal_subject_,
                 std::string birthday_date_,
                 std::string address_,
                 std::string passport_,
                 std::string debet_,
                 std::string deposit_,
                 std::string credit_);
  std::string GetID();
  std::string GetName();
  std::string GetLegalSubject();
  std::string GetBirthDayDate();
  std::string GetAddress();
  std::string GetPassport();
  std::string GetDeposit();
  std::string GetDebit();
  std::string GetCredit();
  friend CreaterPhysicalPerson;
};

class IBankManager {
 public:
  virtual void WriteID() = 0;
  virtual void WriteName() = 0;
  virtual void WriteLegalSubject(std::string) = 0;
  virtual void WriteBirthDayDate() = 0;
  virtual void WriteAddress() = 0;
  virtual void WritePassport() = 0;
  virtual PhysicalClient *GetClient() = 0;
};
class CreaterPhysicalPerson : public IBankManager {
 private:
  PhysicalClient *physical_client_;
 public:
  friend PhysicalClient;
  CreaterPhysicalPerson();

  ~CreaterPhysicalPerson();
  void WriteID() override;
  void WriteName() override;
  void WriteLegalSubject(std::string legal_subject) override;
  void WriteBirthDayDate() override;
  void WriteAddress() override;
  void WritePassport() override;

  PhysicalClient *GetClient() override;

};

void WriteDataAboutClientToSQL(PhysicalClient *client, std::string bank);

#endif //SQLBD__REGISTRATION_H_
