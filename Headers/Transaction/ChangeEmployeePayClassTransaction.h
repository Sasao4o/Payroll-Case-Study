 
 #include "./ChangeEmployeeTransaction.h"
 #include "../PayClassification/PayClassification.h"
    #ifndef ChangeEmpPayClassHeader 
    #define ChangeEmpPayClassHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::Classification::PayClassification;
    using PayrollCaseStudy::PayrollEMPDB::Employee;
    using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
class ChangeEmployeePayClassTransaction : public ChangeEmployeeTransaction {
    public:
    

  
    ChangeEmployeePayClassTransaction(int id);

 
    void Change(Employee* emp);
   virtual PayClassification* getClassification() = 0;
   virtual PaymentSchedule*  getSchedule() = 0;
    
};
}
     }
    #endif