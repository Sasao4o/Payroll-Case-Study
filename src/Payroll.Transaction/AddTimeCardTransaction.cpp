 
 

    #include "../../Headers/Transaction/AddTimeCardTransaction.h"
     #include "../../Headers/PayClassification/HourlyPayClassification.h"
         using namespace PayrollCaseStudy::PayrollEMPDB;
          namespace PayrollCaseStudy {
                using PayrollCaseStudy::Classification::HourlyPayClassification;
namespace TransactionBag {
    AddTimeCardTransaction::AddTimeCardTransaction(int id,std::time_t time, int hours) {
        this->employeeId = id;
              this->time = time;
                    this->hours = hours;
    }
    void AddTimeCardTransaction::Execute() {
            Employee *myEmployee = (PayrollDatabase::instance)->getEmployee(employeeId);
            if (myEmployee == 0) {
                return;
            }

            HourlyPayClassification *payClass =   dynamic_cast<HourlyPayClassification *>(myEmployee->getPaymentClassification());
            //if this down cast fails it means that the employee is not classified as hourly pay
            if (payClass == nullptr) return;
            // payClass->insertTimeCard(time,hours);
            (PayrollDatabase::instance)->AddTimeCard(myEmployee, time, hours);
            // payClass->insertTimeCard();
    }   

}
          }