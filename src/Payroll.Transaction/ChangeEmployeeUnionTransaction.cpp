#include "../../Headers/Transaction/ChangeEmployeeUnionTransaction.h"

#include "../../Headers/Affiliation/UnionAffiliation.h"

namespace PayrollCaseStudy {

  namespace TransactionBag {
    using PayrollCaseStudy::AffiliationBag::UnionAffiliation;
    using PayrollCaseStudy::PayrollEMPDB::PayrollDatabase;
    ChangeEmployeeUnionTransaction::ChangeEmployeeUnionTransaction(int id, int memberId, int weeklyDues): ChangeEmployeeAffiliationTransaction(id) {
      this -> memberId = memberId;
      this -> weeklyDues = weeklyDues;
    }

    Affiliation * ChangeEmployeeUnionTransaction::getAffiliation() {
      return (new UnionAffiliation(memberId, weeklyDues));
    }
    void ChangeEmployeeUnionTransaction::RecordMemberShip(Employee * emp) {
   UnionAffiliation *uf =   dynamic_cast<UnionAffiliation *>((PayrollDatabase::instance)->getEmployee(emp->id)->unionAff);
      if (uf != 0) {
     
        (PayrollDatabase::instance) -> DeleteUnionMember(uf -> memberId);
      }
      (PayrollDatabase::instance) -> AddUnionMember(memberId, emp);
    }
  }

}