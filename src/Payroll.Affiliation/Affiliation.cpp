#include "../../Headers/Affiliation/Affiliation.h"


    
namespace PayrollCaseStudy {
    namespace AffiliationBag {
    bool Affiliation::isInPayPeriod(std::time_t currentDate , std::time_t startPeriod, std::time_t endPeriod) {
    return currentDate >= startPeriod && endPeriod >= currentDate;
    }

    }
}