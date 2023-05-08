 
   #include "../../Headers/Transaction/AddEmployeeTransaction.h"
 

 #include "../../Headers/PayClassification/PayClassification.h"
  #include "../../Headers/Affiliation/UnionAffiliation.h"
  // #include "../Payroll.Methods/HoldPayMethod.cpp"
  #include "../../Headers/PayMethod/HoldPayMethod.h"
    #include "../../Headers/PayMethod/DirectPayMethod.h"
#include<iostream>
        // #include "../Payroll.Schedules/WeeklyPaymentSchedule.cpp"
        // #include "../Payroll.Schedules/MonthlyPaymentSchedule.cpp"
        using namespace PayrollCaseStudy::PayrollEMPDB;
        using namespace PayrollCaseStudy::Classification;
        using namespace PayrollCaseStudy::SchedulesBag;
        using namespace PayrollCaseStudy::MethodsBag;
         namespace PayrollCaseStudy {

namespace TransactionBag {
   AddEmpoloyeeTransaction::AddEmpoloyeeTransaction(int id,std::string name, std::string email, int age, std::string address) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->age = age;
        this->address = address;
    }
    
    
  
    void AddEmpoloyeeTransaction::Execute() {
         
        PayClassification *payClass = MakeClassification();
        PaymentSchedule *paySchedule = MakeSchedule();
        // PayMethod *payMethod = new HoldPayMethod();
        PayMethod *payMethod = new DirectPayMethod("dummy" + std::to_string(id), "dummy" + std::to_string(id));

        Employee *e = new Employee(id, name, email, age,address, payClass,payMethod);
        e->setPaySchedule(paySchedule);
        (PayrollDatabase::instance)->AddEmployee(e->id, e);
       
    }

}
         }