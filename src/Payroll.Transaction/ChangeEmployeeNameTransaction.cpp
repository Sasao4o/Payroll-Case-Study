#include "../../Headers/Transaction/ChangeEmployeeNameTransaction.h"

    namespace PayrollCaseStudy {

namespace TransactionBag {


    ChangeEmployeeNameTransaction::ChangeEmployeeNameTransaction(int id, std::string name) : ChangeEmployeeTransaction(id) {
        this->name = name;
    }

    void ChangeEmployeeNameTransaction::Change(Employee *emp) {
        (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->UpdateEmployee(id, "Name", name);
    }
}

    }