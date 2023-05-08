   #ifndef PayClassificationHeader
 #define PayClassificationHeader
#include<ctime>
namespace PayrollCaseStudy {
  namespace Classification {
class PayClassification {
    public:
    virtual float calculatePay(time_t startPeriod, time_t endPeriod) = 0;
      bool isInPayPeriod(std::time_t currentDate , std::time_t startPeriod, std::time_t endPeriod) {
        return currentDate >= startPeriod && endPeriod >= currentDate;
    }
};
 
  }
}
#endif
  