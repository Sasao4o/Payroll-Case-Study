   #include "../../Headers/Transaction/AddComissionEmployeeTransaction.h"
   #include "../../Headers/PayClassification/PayClassification.h"
    //  #include "../Payroll.Classification/ComissionPayClassification.cpp"
    #include "../../Headers/PayClassification/ComissionPayClassification.h"
    #include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"
        #include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"
       
namespace PayrollCaseStudy {

namespace TransactionBag {
     using PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule;
     using PayrollCaseStudy::Classification::PayClassification;
     using PayrollCaseStudy::Classification::ComissionPayClassification;
     using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
     using PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule;
    AddComissionEmployeeTransaction::AddComissionEmployeeTransaction(int id,std::string name, std::string email, int age, int baseRate, float comissionRate, std::string address)
        : AddEmpoloyeeTransaction(id, name, email, age,  address)
     {
        this->baseRate =  baseRate;
        this->comissionRate = comissionRate;
    } 

     PayClassification *AddComissionEmployeeTransaction::MakeClassification() {
            return (new ComissionPayClassification(baseRate, comissionRate));
    }   
    PaymentSchedule* AddComissionEmployeeTransaction::MakeSchedule() {
            return (new MonthlyPaymentSchedule());
    }
   };
}
