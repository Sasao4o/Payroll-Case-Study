 
 #include "./ChangeEmployeeTransaction.h"
 #include "../PayClassification/PayClassification.h"
    #ifndef ChangeEmpMethodHeader 
    #define ChangeEmpMethodHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::PayrollEMPDB::Employee;
     
class ChangeEmployeeMethodTransaction : public ChangeEmployeeTransaction {
    public:
    

  
    ChangeEmployeeMethodTransaction(int id);
    void Change(Employee* emp);
    virtual PayMethod* getPayMethod() = 0;
 
    
};
}
     }
    #endif