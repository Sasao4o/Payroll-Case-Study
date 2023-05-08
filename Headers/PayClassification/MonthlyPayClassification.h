 #include "./PayClassification.h"
#ifndef MonthlyPayClassHeader
#define MonthlyPayClassHeader
namespace PayrollCaseStudy {
  namespace Classification {

 
 
class MonthlyPayClassification : public PayClassification {
    public:
    int monthlyPay;
    MonthlyPayClassification(int salary);
    float calculatePay(time_t startPeriod, time_t endPeriod);

};
 

 
  }
}

 #endif