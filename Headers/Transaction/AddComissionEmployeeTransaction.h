   #include "./AddEmployeeTransaction.h"
namespace PayrollCaseStudy {

namespace TransactionBag {
   class AddComissionEmployeeTransaction : public AddEmpoloyeeTransaction {
        public:
        AddComissionEmployeeTransaction(int id,std::string name, std::string email, int age, int baseRate, float commisionRate,std::string address);
         PayrollCaseStudy::SchedulesBag::PaymentSchedule* MakeSchedule();
       PayrollCaseStudy::Classification::PayClassification* MakeClassification();
      int baseRate;
     float comissionRate;
   };
}
}