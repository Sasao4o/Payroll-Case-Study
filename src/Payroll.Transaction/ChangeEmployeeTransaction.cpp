 
#include "../../Headers/Transaction/ChangeEmployeeTransaction.h"
// #include "../Payroll.Affiliation/UnionAffiliation.cpp"
#include "../../Headers/Affiliation/UnionAffiliation.h"
     using namespace PayrollCaseStudy::PayrollEMPDB;
     using namespace PayrollCaseStudy::AffiliationBag;
     using PayrollCaseStudy::MethodsBag::PayMethod;
     using PayrollCaseStudy::Classification::PayClassification;
  namespace PayrollCaseStudy {

namespace TransactionBag {
    ChangeEmployeeTransaction::ChangeEmployeeTransaction(int id) {
       
         this->id = id;
  
    }
    

 
    void ChangeEmployeeTransaction::Execute() {
        Employee * currentEmp = (PayrollDatabase::instance)->getEmployee(id);
        if (currentEmp ==  0 ) return;
        Change(currentEmp); 
    }
    
}
  }