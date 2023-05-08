  #ifndef AddHourlyHeader
  #define AddHourlyHeader
  
   #include "./AddEmployeeTransaction.h"
namespace PayrollCaseStudy {

namespace TransactionBag {
   class AddHourlyEmployeeTransaction :public AddEmpoloyeeTransaction {
        public:
        AddHourlyEmployeeTransaction(int id,std::string name, std::string email, int age, float hourRate, std::string address);
         PayrollCaseStudy::SchedulesBag::PaymentSchedule* MakeSchedule();
       PayrollCaseStudy::Classification::PayClassification* MakeClassification();
        float hourRate;
   };
}
}

#endif