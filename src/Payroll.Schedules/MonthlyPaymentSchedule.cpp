#include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"
#include<ctime>
  namespace PayrollCaseStudy {
    namespace SchedulesBag {
 bool MonthlyPaymentSchedule::IsLastDayOfMonth(std::time_t date)
        {
          tm *ltm = localtime(&date);
          //company policy l abd 3n 28 mlk4 d3wa :D
            return ltm->tm_mday == 28;
 
        }
        bool MonthlyPaymentSchedule::isPayDate(std::time_t payDate)
    {
        // return IsLastDayOfMonth(payDate);
        return 1;
    }

    std::time_t MonthlyPaymentSchedule::getPayStartPeriod(time_t payDate)  {
        return payDate - 24 * (24 * 60 * 60);
    }
    }
  }