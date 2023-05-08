 #ifndef AffiliationHeader
 #define AffiliationHeader
#include<ctime>
namespace PayrollCaseStudy {
    namespace AffiliationBag {
class Affiliation {
    public:
    
    virtual float calculateDeductions(time_t startPeriod, time_t endPeriod) = 0;
    bool isInPayPeriod(std::time_t currentDate , std::time_t startPeriod, std::time_t endPeriod);
    virtual int getDues() = 0;

};
    }
}
 #endif