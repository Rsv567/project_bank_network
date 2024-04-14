#ifndef SQLBD__STATECLIENT_H_
#define SQLBD__STATECLIENT_H_
#include "InputOutputData.h"
#include "Registration.h"
#include "AccountOpening.h"
#include "bank_transfer.h"
class State {
 public:
  virtual void Input(std::string bank) = 0;
};

class RegistrationState : public State {
  void Input(std::string bank) override;
};

class OpenAccountState : public State {
  void Input(std::string bank) override;
};

class TopUpState : public State {
  void Input(std::string bank) override;
};

class WithdrawState : public State {
  void Input(std::string bank) override;
};

class CloseState : public State {
  void Input(std::string bank) override;
};

class TransferAnotherBankState : public State {
  void Input(std::string bank) override;
};

class TransactionWithinBankState : public State {
  void Input(std::string bank) override;
};

class CanselTransactionWithinBankState : public State {
  void Input(std::string bank) override;
};

class CanselTransactionAnotherBankState : public State {
  void Input(std::string bank) override;
};

class Context {
 private:
  State *state_;
 public:
  Context() : state_(new RegistrationState) {}
  void SetState(State *new_state) {
    delete state_;
    state_ = new_state;
  }
  void Change(std::string bank) {
    state_->Input(bank);
  }
};
#endif //SQLBD__STATECLIENT_H_
