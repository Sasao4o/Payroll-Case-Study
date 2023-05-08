 
 
#include "../../Headers/PayClassification/MonthlyPayClassification.h"
 
 namespace PayrollCaseStudy {
  namespace Classification {

    MonthlyPayClassification::MonthlyPayClassification(int salary) {
            monthlyPay = salary;
    }
    float MonthlyPayClassification::calculatePay(time_t startPeriod, time_t endPeriod) {
 
        return (float)monthlyPay;
    }

}
 }
