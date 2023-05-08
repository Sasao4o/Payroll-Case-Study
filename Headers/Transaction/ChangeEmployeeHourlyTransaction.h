 
 #include "./ChangeEmployeePayClassTransaction.h"
 
    #ifndef ChangeEmployeeHourlyHeader 
    #define ChangeEmployeeHourlyHeader
      
     namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::PayrollEMPDB::Employee;
    using PayrollCaseStudy::Classification::PayClassification;
    using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
class ChangeEmployeeHourlyTransaction : public ChangeEmployeePayClassTransaction {
    public:
    
    int hourRate;
    
    ChangeEmployeeHourlyTransaction(int id, int hourRate);
        PayClassification* getClassification();
         PaymentSchedule*  getSchedule();
};
}
     }
    #endif