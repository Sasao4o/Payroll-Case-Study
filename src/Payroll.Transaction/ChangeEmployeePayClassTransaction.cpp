#include "../../Headers/Transaction/ChangeEmployeePayClassTransaction.h"

    namespace PayrollCaseStudy {

namespace TransactionBag {

    using PayrollCaseStudy::Classification::PayClassification;
    ChangeEmployeePayClassTransaction::ChangeEmployeePayClassTransaction(int id) : ChangeEmployeeTransaction(id) {
       
    }

    void ChangeEmployeePayClassTransaction::Change(Employee *emp) {
         
        // emp->setPayClass(getClassification());
    
        // emp->setPaySchedule(getSchedule());
    (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->UpdateEmpPayClass(emp->id, getClassification());
        (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->UpdateEmpPaySchedule(emp->id, getSchedule());
    }
}

    }