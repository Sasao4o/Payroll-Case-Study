#include "../../Headers/Transaction/ChangeEmployeeHoldMethodTransaction.h"

#include "../../Headers/PayMethod/HoldPayMethod.h"

namespace PayrollCaseStudy {

  namespace TransactionBag {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::MethodsBag::HoldPayMethod;
    ChangeEmployeeHoldMethodTransaction::ChangeEmployeeHoldMethodTransaction(int id): ChangeEmployeeMethodTransaction(id) {
       
    }

    PayMethod * ChangeEmployeeHoldMethodTransaction::getPayMethod() {
      return (new HoldPayMethod());
    }

  }
}