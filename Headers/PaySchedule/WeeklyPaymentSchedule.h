#include "./PaymentSchedule.h"
#include<ctime>
#ifndef WeeklyPaymentScheduleHeader
#define WeeklyPaymentScheduleHeader
 namespace PayrollCaseStudy {
    namespace SchedulesBag {
class WeeklyPaymentSchedule : public PaymentSchedule {

    public:
    bool IsLastDayOfWeek(std::time_t date);
    bool isPayDate(std::time_t payDate);
    std::time_t getPayStartPeriod(time_t payDate);
     
};
    }
 }
#endif
