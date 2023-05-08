#include "./Transaction.h"
 #include "../PayMethod/PayMethod.h"
 #include "../Database/Employee.h"
    #ifndef ChangeEmpHeader 
    #define ChangeEmpHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
class ChangeEmployeeTransaction : public Transaction {
    public:
    int id;
 
    ChangeEmployeeTransaction(int id);
    virtual void Change(Employee* emp) = 0;
 
    void Execute();
    
};
}
     }
    #endif