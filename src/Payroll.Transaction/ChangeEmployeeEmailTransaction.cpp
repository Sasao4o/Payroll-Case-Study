#include "../../Headers/Transaction/ChangeEmployeeEmailTransaction.h"

    namespace PayrollCaseStudy {

namespace TransactionBag {


    ChangeEmployeeEmailTransaction::ChangeEmployeeEmailTransaction(int id, std::string email) : ChangeEmployeeTransaction(id) {
        this->email = email;
    }

    void ChangeEmployeeEmailTransaction::Change(Employee *emp) {
                (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->UpdateEmployee(id, "Email", email);
    }
}

    }