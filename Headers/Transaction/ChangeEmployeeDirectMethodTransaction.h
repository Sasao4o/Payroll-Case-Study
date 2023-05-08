 
 #include "./ChangeEmployeeMethodTransaction.h"
 #include<string>
    #ifndef ChangeEmpDirectMethodHeader 
    #define ChangeEmpDirectMethodHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
 
    using PayrollCaseStudy::MethodsBag::PayMethod;
class ChangeEmployeeDirectMethodTransaction : public ChangeEmployeeMethodTransaction {
    public:
    
    std::string bankAccount;
      std::string account;
    
    ChangeEmployeeDirectMethodTransaction(int id, std::string bankAccount, std::string account);
         PayMethod*  getPayMethod();
};
}
     }
    #endif