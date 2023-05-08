#include "../../Headers/Transaction/ChangeEmployeeDirectMethodTransaction.h"

#include "../../Headers/PayMethod/DirectPayMethod.h"

namespace PayrollCaseStudy {

  namespace TransactionBag {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::MethodsBag::DirectPayMethod;
    ChangeEmployeeDirectMethodTransaction::ChangeEmployeeDirectMethodTransaction(int id, std::string bankAccount, std::string account): ChangeEmployeeMethodTransaction(id) {
      this -> bankAccount = bankAccount;
      this->account = account;
    }

    PayMethod * ChangeEmployeeDirectMethodTransaction::getPayMethod() {
      return (new DirectPayMethod(bankAccount, account));
    }

  }
}