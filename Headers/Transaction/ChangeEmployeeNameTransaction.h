 
 #include "./ChangeEmployeeTransaction.h"
 
    #ifndef ChangeEmpNameHeader 
    #define ChangeEmpNameHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
class ChangeEmployeeNameTransaction : public ChangeEmployeeTransaction {
    public:
    
    std::string name;
  
    ChangeEmployeeNameTransaction(int id, std::string name);
 
 
    void Change(Employee* emp);
    
};
}
     }
    #endif