
#ifndef PaymentScheduleHeader
#define PaymentScheduleHeader
#include<ctime>
 
 namespace PayrollCaseStudy {
    namespace SchedulesBag {
class PaymentSchedule {
    public:
    virtual bool isPayDate(time_t payDate) = 0;
    virtual std::time_t getPayStartPeriod(time_t payDate) = 0;
};

    }
 }
 
 #endif