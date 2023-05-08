#include "../../Headers/Transaction/ChangeEmployeeMailMethodTransaction.h"

#include "../../Headers/PayMethod/MailPayMethod.h"
namespace PayrollCaseStudy {

  namespace TransactionBag {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::MethodsBag::MailPayMethod;
    ChangeEmployeeMailMethodTransaction::ChangeEmployeeMailMethodTransaction(int id, std::string mailAddress): ChangeEmployeeMethodTransaction(id) {
        this->mailAddress = mailAddress;
    }

    PayMethod * ChangeEmployeeMailMethodTransaction::getPayMethod() {
      return (new MailPayMethod(mailAddress));
    }

  }
}