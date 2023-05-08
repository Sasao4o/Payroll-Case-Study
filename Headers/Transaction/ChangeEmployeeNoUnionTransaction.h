 
 #include "./ChangeEmployeeAffiliationTransaction.h"
 
    #ifndef ChangeEmpNoUnionAffiliationHeader 
    #define ChangeEmpNoUnionAffiliationHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
     using PayrollCaseStudy::AffiliationBag::Affiliation;
class ChangeEmployeeNoUnionTransaction : public ChangeEmployeeAffiliationTransaction {
    public:
    
     
    
    ChangeEmployeeNoUnionTransaction(int id);
        Affiliation* getAffiliation();
         void  RecordMemberShip(Employee *emp);
};
}
     }
    #endif