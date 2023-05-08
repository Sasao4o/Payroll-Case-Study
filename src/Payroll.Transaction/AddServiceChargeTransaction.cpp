#include "../../Headers/Transaction/AddServiceChargeTransaction.h"
 
     using namespace PayrollCaseStudy::PayrollEMPDB;
     using namespace PayrollCaseStudy::AffiliationBag;
  namespace PayrollCaseStudy {

namespace TransactionBag {
    AddServiceChargeTransaction::AddServiceChargeTransaction(int memberId, time_t time, int charge) {
        this->memberId = memberId;
        this->time = time;
        this->charge = charge;
    }
    void AddServiceChargeTransaction::Execute() {
        int empId = (PayrollDatabase::instance)->getUnionMember(memberId);
            //what is the memberId is wrong
        Employee *myEmp = (PayrollDatabase::instance)->getEmployee(empId);
        if (myEmp == 0) return;
        (PayrollDatabase::instance)->AddSerivceCharge(myEmp, time, charge);
    }
}
  }