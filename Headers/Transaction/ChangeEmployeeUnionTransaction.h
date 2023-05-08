 
 #include "./ChangeEmployeeAffiliationTransaction.h"
 
    #ifndef ChangeEmpUnionAffiliationHeader 
    #define ChangeEmpUnionAffiliationHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
    using PayrollCaseStudy::Classification::PayClassification;
    using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
class ChangeEmployeeUnionTransaction : public ChangeEmployeeAffiliationTransaction {
    public:
    
    int memberId;
    int weeklyDues;
    
    ChangeEmployeeUnionTransaction(int id, int memberId, int weeklyDues);
        Affiliation* getAffiliation();
         void  RecordMemberShip(Employee *emp);
};
}
     }
    #endif