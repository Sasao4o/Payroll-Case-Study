#include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"

namespace PayrollCaseStudy {
  namespace SchedulesBag {

    bool WeeklyPaymentSchedule::IsLastDayOfWeek(std::time_t date) {
      tm * ltm = localtime( & date);

      return ltm -> tm_mday % 7 == 0;

    }
    bool WeeklyPaymentSchedule::isPayDate(std::time_t payDate) {
      return true;
      // return IsLastDayOfWeek(payDate);
    }

    std::time_t WeeklyPaymentSchedule::getPayStartPeriod(time_t payDate) {
      return payDate - 5 * (24 * 60 * 60);
    }
  }
}