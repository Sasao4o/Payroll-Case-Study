#include "../../Headers/Transaction/ChangeEmployeeMethodTransaction.h"

    namespace PayrollCaseStudy {

namespace TransactionBag {

    using PayrollCaseStudy::Classification::PayClassification;
    ChangeEmployeeMethodTransaction::ChangeEmployeeMethodTransaction(int id) : ChangeEmployeeTransaction(id) {
       
    }

    void ChangeEmployeeMethodTransaction::Change(Employee *emp) {
         (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->UpdateEmpPayMethod(emp->id, getPayMethod());
        // emp->setPayMethod(getPayMethod());
    }
}

    }