 #ifndef PayCheckHeader
 #define PayCheckHeader
#include<ctime>
class PayCheck {
    public:
    std::time_t startDate;
    std::time_t endDate;
    float grossPay = 0;
    float deductions = 0;
    float  netPay = 0;
    PayCheck(std::time_t startDate, std::time_t endDate){
        this->startDate = startDate;
        this->endDate = endDate;
    }

};
 
 #endif