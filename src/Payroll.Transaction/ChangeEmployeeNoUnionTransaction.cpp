#include "../../Headers/Transaction/ChangeEmployeeNoUnionTransaction.h"
 #include "../../Headers/Affiliation/NoAffiliation.h"
  #include "../../Headers/Affiliation/UnionAffiliation.h"
    namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::AffiliationBag::NoAffiliation;

    //This bad design as NoAffiliation shouldn't know about Affiliation
      using PayrollCaseStudy::AffiliationBag::UnionAffiliation;
        using PayrollCaseStudy::PayrollEMPDB::PayrollDatabase;
    ChangeEmployeeNoUnionTransaction::ChangeEmployeeNoUnionTransaction(int id) : ChangeEmployeeAffiliationTransaction(id) {
    
    }

       Affiliation* ChangeEmployeeNoUnionTransaction::getAffiliation() {
                return (new NoAffiliation());
       }
        void ChangeEmployeeNoUnionTransaction::RecordMemberShip(Employee *emp) {
          //This is bad as the NonUnionAffiliation shouldn't know about the union affilication
          // so it is slightly violates OCP
      UnionAffiliation *uf =   dynamic_cast<UnionAffiliation *>((PayrollDatabase::instance)->getEmployee(emp->id)->unionAff);
      if (uf == 0) return;
          (PayrollDatabase::instance)->DeleteUnionMember(uf->memberId);
        }
}

    }