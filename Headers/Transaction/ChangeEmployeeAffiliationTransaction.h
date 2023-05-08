 
 #include "./ChangeEmployeeTransaction.h"
 #include "../Affiliation/Affiliation.h"
    #ifndef ChangeEmpAffiliationHeader 
    #define ChangeEmpAffiliationHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::AffiliationBag::Affiliation;
    using PayrollCaseStudy::PayrollEMPDB::Employee;
 
class ChangeEmployeeAffiliationTransaction : public ChangeEmployeeTransaction {
    public:
    

  
    ChangeEmployeeAffiliationTransaction(int id);

 
    void Change(Employee* emp);
 
   virtual Affiliation*  getAffiliation() = 0;
   virtual void  RecordMemberShip(Employee * emp) = 0;
};
}
     }
    #endif