   #include "../../Headers/Transaction/AddSalariedEmployeeTransaction.h"
   #include "../../Headers/PayClassification/PayClassification.h"
    #include "../../Headers/PayClassification/MonthlyPayClassification.h"
        #include "../../Headers/PaySchedule/PaymentSchedule.h"
         #include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"
   //   #include "../Payroll.Classification/MonthlyPayClassification.cpp"
 
     using PayrollCaseStudy::Classification::PayClassification;
     using PayrollCaseStudy::Classification::MonthlyPayClassification;
     using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
     using PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule;

namespace PayrollCaseStudy {

namespace TransactionBag {
 
    AddSalariedEmployeeTransaction::AddSalariedEmployeeTransaction(int id,std::string name, std::string email, int age,int salary, std::string address)
        : AddEmpoloyeeTransaction(id, name, email, age, address)
     {
     
        this->salary = salary;
    } 

     PayClassification *AddSalariedEmployeeTransaction::MakeClassification() {
            return (new MonthlyPayClassification(salary));
    }   
    PaymentSchedule *AddSalariedEmployeeTransaction::MakeSchedule() {
      return (new MonthlyPaymentSchedule());
    }
   };
}
