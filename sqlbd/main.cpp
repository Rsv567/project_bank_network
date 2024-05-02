#include "header/StateClient.h"
#include "header/create_data_base.h"

int main() {
  CreateDataBase();
  bool exit = false;
  while (exit == false) {
   std::unique_ptr<InputData> output_data(new GraphicsInput("which_bank"));
    std::string bank;
    output_data->input(bank);
    std::cout<<bank;
    std::unique_ptr<InputData> out_data (new GraphicsInput("hello"));
    std::string input_;
    out_data->input(input_);
std::cout<<input_;
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
    std::unique_ptr<InputData> out_datax( new GraphicsInput("continue"));
    out_datax->input(session_continued);
    exit = (session_continued != "yes");
  }
}
