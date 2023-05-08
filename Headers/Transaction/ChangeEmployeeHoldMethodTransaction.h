 
 #include "./ChangeEmployeeMethodTransaction.h"
 #include<string>
    #ifndef ChangeEmpHoldMethodHeader 
    #define ChangeEmpHoldMethodHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
 
    using PayrollCaseStudy::MethodsBag::PayMethod;
class ChangeEmployeeHoldMethodTransaction : public ChangeEmployeeMethodTransaction {
    public:
    
    std::string bankAccount;
    
    ChangeEmployeeHoldMethodTransaction(int id);
         PayMethod*  getPayMethod();
};
}
     }
    #endif