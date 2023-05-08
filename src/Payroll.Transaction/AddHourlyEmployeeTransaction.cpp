   #include "../../Headers/Transaction/AddHourlyEmployeeTransaction.h"
   #include "../../Headers/PayClassification/PayClassification.h"
      #include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"
      #include "../../Headers/PayClassification/HourlyPayClassification.h"
   //   #include "../Payroll.Classification/MonthlyPayClassification.cpp"
            #include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"
    
namespace PayrollCaseStudy {

namespace TransactionBag {
        using PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule;
     using PayrollCaseStudy::Classification::PayClassification;
     using PayrollCaseStudy::Classification::HourlyPayClassification;
     using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
     using PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule;
    AddHourlyEmployeeTransaction::AddHourlyEmployeeTransaction(int id,std::string name, std::string email, int age,float hourRate, std::string address)
        : AddEmpoloyeeTransaction(id, name, email, age, address)
     {
     
        this->hourRate = hourRate;
    } 

     PayClassification *AddHourlyEmployeeTransaction::MakeClassification() {
            return (new HourlyPayClassification(hourRate));
    }   

    PaymentSchedule* AddHourlyEmployeeTransaction::MakeSchedule() {
            return (new WeeklyPaymentSchedule());
    }
   };
}
