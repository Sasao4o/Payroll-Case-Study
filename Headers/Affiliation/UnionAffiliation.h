 #ifndef UnionAffiliationHeader
 #define UnionAffiliationHeader
#include <map>
#include <ctime>
#include<math.h>
#include "./Affiliation.h"
#include <stdexcept>
#include<iostream>
namespace PayrollCaseStudy {
    namespace AffiliationBag {
class UnionAffiliation : public Affiliation {
    public: 
    std::map<std::time_t, int> serviceCharge;
    int weeklyDues;
    int memberId;
    UnionAffiliation(int memberId, int weeklyDues);
    int getServiceCharge(time_t timeC);
    void addServiceCharge(time_t time, int charge);
    float calculateDeductions(time_t startPeriod, time_t endPeriod);
    int getDues();
};
    }
}
 #endif