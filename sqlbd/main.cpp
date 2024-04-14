#include "header/StateClient.h"
#include "header/create_data_base.h"
int main() {
  CreateDataBase();
  bool exit = false;
  while (exit == false) {
    OutputData *output_data = new ConsoleOutput;
    output_data->output("which bank you choose(SBERBANK, ALPHABANK, TINKOFF) ");

    InputData *input_data = new ConsoleInput;

    std::string bank;
    input_data->input(bank);

    output_data->output(
        "Hello. What kind of service do you want.(registration, open account, top up, withdraw, close account,\n" \
         "transfer money to another account in our bank,transfer money to another account in other bank,\n cancel transaction within the bank,"\
         "cancel transaction money to another account in other bank):\n");
    std::string input_;
    input_data->input(input_);

    if (input_ == "registration") {

      State *reg = new RegistrationState;
      reg->Input(bank);

    } else if (input_ == "open account") {

      State *open_account_state = new OpenAccountState;
      open_account_state->Input(bank);

    } else if (input_ == "top up") {

      State *top_up_state = new TopUpState;
      top_up_state->Input(bank);

    } else if (input_ == "withdraw") {

      State *withdraw_state = new WithdrawState;
      withdraw_state->Input(bank);

    } else if (input_ == "close account") {

      State *close_state = new CloseState;
      close_state->Input(bank);

    } else if (input_ == "transfer money to another account in our bank") {

      State *transaction_within_bank_state = new TransactionWithinBankState;
      transaction_within_bank_state->Input(bank);

    } else if (input_ == "cancel transaction within the bank") {

      State *cansel_transaction_within_bank_state = new CanselTransactionWithinBankState;
      cansel_transaction_within_bank_state->Input(bank);

    } else if (input_ == "transfer money to another account in other bank") {

      State *transfer_another_bank_state = new TransferAnotherBankState;
      transfer_another_bank_state->Input(bank);

    } else if (input_ == "cancel transaction money to another account in other bank") {

      State *cansel_transaction_another_bank_state = new CanselTransactionAnotherBankState;
      cansel_transaction_another_bank_state->Input(bank);

    }
    std::string session_continued;
    output_data->output("\nif you want to continue, write yes or no. ");
    input_data->input(session_continued);
    exit = (session_continued != "yes");
  }
}
