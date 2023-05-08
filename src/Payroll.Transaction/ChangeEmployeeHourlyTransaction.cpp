#include "../../Headers/Transaction/ChangeEmployeeHourlyTransaction.h"
#include "../../Headers/PayClassification/HourlyPayClassification.h"
         #include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"
    namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::Classification::HourlyPayClassification;
    using PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule;

    ChangeEmployeeHourlyTransaction::ChangeEmployeeHourlyTransaction(int id, int hourRate) : ChangeEmployeePayClassTransaction(id) {
        this->hourRate = hourRate;
    }

       PayClassification* ChangeEmployeeHourlyTransaction::getClassification() {
                return (new HourlyPayClassification(hourRate));
       }
         PaymentSchedule*  ChangeEmployeeHourlyTransaction::getSchedule() {
                 return (new MonthlyPaymentSchedule());
         }
}

    }