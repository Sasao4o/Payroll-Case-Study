#include "../../Headers/Transaction/ChangeEmployeeAffiliationTransaction.h"

    namespace PayrollCaseStudy {

namespace TransactionBag {

    using PayrollCaseStudy::Classification::PayClassification;
    ChangeEmployeeAffiliationTransaction::ChangeEmployeeAffiliationTransaction(int id) : ChangeEmployeeTransaction(id) {
       
    }

    void ChangeEmployeeAffiliationTransaction::Change(Employee *emp) {
                emp->setUnionAff(getAffiliation());
                 RecordMemberShip(emp);
    
                
    }
}

    }