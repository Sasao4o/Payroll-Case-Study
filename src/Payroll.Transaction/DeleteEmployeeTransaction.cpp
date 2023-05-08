#include "../../Headers/Transaction/DeleteEmployeeTransaction.h"
        using namespace PayrollCaseStudy::PayrollEMPDB;
  namespace PayrollCaseStudy {

namespace TransactionBag {
    DeleteEmployeeTransaction::DeleteEmployeeTransaction(int id) {
        this->employeeId = id;
    }
    void DeleteEmployeeTransaction::Execute() {
        //here we take to the database and add the employee
        // std::cout << "DELETE FROM EMPLOYEE WHERE ID =  ("  << this->employeeId << ")";
        (PayrollDatabase::instance)->DeleteEmployee(employeeId);
    }
}
  }