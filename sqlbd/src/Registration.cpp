#include "Registration.h"


PhysicalClient::PhysicalClient()
    : id(""),
      name(""),
      legal_subject(""),
      birthday_date(""),
      address(""),
      passport(""),
      debit(""),
      deposit(""),
      credit("") {
}
PhysicalClient::PhysicalClient(std::string id_,
                               std::string name_,
                               std::string legal_subject_,
                               std::string birthday_date_,
                               std::string address_,
                               std::string passport_,
                               std::string debit_,
                               std::string deposit_,
                               std::string credit_)
    : id(id_),
      name(name_),
      legal_subject(legal_subject_),
      birthday_date(birthday_date_),
      address(address_),
      passport(passport_),
      debit(debit_),
      deposit(deposit_),
      credit(credit_) {
}
std::string PhysicalClient::GetID() {
  return id;
}
std::string PhysicalClient::GetName() {
  return name;
}
std::string PhysicalClient::GetLegalSubject() {
  return legal_subject;
}
std::string PhysicalClient::GetBirthDayDate() {
  return birthday_date;
}
std::string PhysicalClient::GetAddress() {
  return address;
}
std::string PhysicalClient::GetPassport() {
  return passport;
}

CreaterPhysicalPerson::CreaterPhysicalPerson() : physical_client_(new PhysicalClient) {
}
CreaterPhysicalPerson::~CreaterPhysicalPerson() {
  delete physical_client_;
}
void CreaterPhysicalPerson::WriteID() {

  std::getline(std::cin, physical_client_->id);

}
void CreaterPhysicalPerson::WriteName() {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_name"));
  out_data->input(physical_client_->name);

}
void CreaterPhysicalPerson::WriteLegalSubject(std::string legal_subject) {
  physical_client_->legal_subject = legal_subject;
}
void CreaterPhysicalPerson::WriteBirthDayDate() {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_birth"));
  out_data->input(physical_client_->birthday_date);
}
void CreaterPhysicalPerson::WriteAddress() {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_address"));
  out_data->input( physical_client_->address);

}
void CreaterPhysicalPerson::WritePassport() {
  std::unique_ptr<InputData> out_data(new GraphicsInput("write_passport"));
  out_data->input( physical_client_->passport);

}

PhysicalClient *CreaterPhysicalPerson::GetClient() {
  return physical_client_;
}

void WriteDataAboutClientToSQL(PhysicalClient *client, std::string bank) {
  // Формирование строки SQL запроса
  std::string
      sql = insert_into + bank + " (ID, NAME,LEGALSUBJECT, BIRTHDAY , ADDRESS, PASSPORT, DEPOSIT, DEBIT,CREDIT )" \
  " VALUES ('100012" + client->GetPassport() + "','" + client->GetName() + "','" + client->GetLegalSubject() + "','"
      + client->GetBirthDayDate() + "','"
      + client->GetAddress() + "','" + client->GetPassport() + "', 'NO','NO','NO'); ";
  OutputData *sql_out = new SQLOutput;
  sql_out->output(sql);
}
