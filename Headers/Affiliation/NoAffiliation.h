 #ifndef NoAffiliationHeader
 #define NoAffiliationHeader
#include <map>
#include <ctime>
#include<math.h>
#include "./Affiliation.h"
namespace PayrollCaseStudy {
    namespace AffiliationBag {
class NoAffiliation : public Affiliation {
    public: 
 
    int getServiceCharge(time_t timeC);
    void addServiceCharge(time_t time, int charge);
    float calculateDeductions(time_t startPeriod, time_t endPeriod);
      int getDues();
};
    }
}
 #endif