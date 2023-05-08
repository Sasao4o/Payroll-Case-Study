#ifndef AddEmployeeTransactionHeader
#define AddEmployeeTransactionHeader
#include "./Transaction.h"
#include "../Affiliation/Affiliation.h"
/*
 #include "../src/Payroll.Classification/HourlyPayClassification.cpp"
  #include "../src/Payroll.Classification/MonthlyPayClassification.cpp"
   #include "../src/Payroll.Classification/ComissionPayClassification.cpp"
 #include "../src/Payroll.Classification/PayClassification.cpp"
  #include "../src/Payroll.Affiliation/UnionAffiliation.cpp"
  #include "../src/Payroll.Methods/HoldPayMethod.cpp"
    #include "../src/Payroll.Schedules/MonthlyPaymentSchedule.cpp"
        #include "../src/Payroll.Schedules/WeeklyPaymentSchedule.cpp"
  */     
 
 namespace PayrollCaseStudy {

namespace TransactionBag {
 class AddEmpoloyeeTransaction : public Transaction {
    public:

    int id;
    std::string name;
    std::string email;
    int age;
    std::string address;
    AddEmpoloyeeTransaction(int id,std::string name, std::string email, int age, std::string address);
     PayrollCaseStudy::SchedulesBag::PaymentSchedule virtual* MakeSchedule() = 0;
     PayrollCaseStudy::Classification::PayClassification virtual *MakeClassification() = 0;
 
    void Execute();

};
}
 }
#endif