 
 #include "./ChangeEmployeeMethodTransaction.h"
 #include<string>
    #ifndef ChangeEmpMailMethodHeader 
    #define ChangeEmpMailMethodHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
 
    using PayrollCaseStudy::MethodsBag::PayMethod;
class ChangeEmployeeMailMethodTransaction : public ChangeEmployeeMethodTransaction {
    public:
    
    std::string mailAddress;
    
    ChangeEmployeeMailMethodTransaction(int id, std::string mailAddress);
    PayMethod*  getPayMethod();
};
}
     }
    #endif