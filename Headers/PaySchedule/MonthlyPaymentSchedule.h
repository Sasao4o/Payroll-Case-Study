#include "./PaymentSchedule.h"

#include<ctime>

#ifndef MonthlyPaymentScheduleH
#define MonthlyPaymentScheduleH
namespace PayrollCaseStudy {
  namespace SchedulesBag {
    class MonthlyPaymentSchedule: public PaymentSchedule {

      public:
      bool IsLastDayOfMonth(std::time_t date);
      bool isPayDate(std::time_t payDate);

      std::time_t getPayStartPeriod(time_t payDate);
    };
  }
}
#endif