#ifndef SQLBD__INTERBANK_TRANSFER_H_
#define SQLBD__INTERBANK_TRANSFER_H_
#include <memory>
#include "InputOutputData.h"
#include "SQLconst.h"
std::string GetIdValueByName(std::string name, std::string bank);
std::string GetTheCurrentValueOfMoneyById(std::string id_client, std::string bank);
void InterbankTransfer(std::string name_decrease,
                       std::string name_increase,
                       std::string amount,
                       std::string bank,
                       std::string is_trans);
void TransferToAnotherBank(std::string name_client_decrease,
                           std::string name_client_increase,
                           std::string amount,
                           std::string bank_client_decrease,
                           std::string bank_client_increase,
                           std::string is_trans);

#endif //SQLBD__INTERBANK_TRANSFER_H_
