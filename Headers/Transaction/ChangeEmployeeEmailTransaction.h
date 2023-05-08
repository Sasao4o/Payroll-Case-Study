 
 #include "./ChangeEmployeeTransaction.h"
 
    #ifndef ChangeEmpEmailHeader 
    #define ChangeEmpEmailHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
class ChangeEmployeeEmailTransaction : public ChangeEmployeeTransaction {
    public:
    
    std::string email;
  
    ChangeEmployeeEmailTransaction(int id, std::string email);
 
 
    void Change(Employee* emp);
    
};
}
     }
    #endif