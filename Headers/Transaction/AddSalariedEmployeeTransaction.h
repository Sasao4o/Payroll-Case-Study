    #ifndef AddSalaryHeader
  #define AddSalaryHeader
  
  
   #include "./AddEmployeeTransaction.h"
namespace PayrollCaseStudy {

namespace TransactionBag {
   class AddSalariedEmployeeTransaction : public AddEmpoloyeeTransaction {
        public:
        AddSalariedEmployeeTransaction(int id,std::string name, std::string email, int age, int salary, std::string address);
         PayrollCaseStudy::SchedulesBag::PaymentSchedule* MakeSchedule();
       PayrollCaseStudy::Classification::PayClassification* MakeClassification();
        int salary;
   };
}
}

#endif