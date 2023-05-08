  
 #ifndef HourlyPayClassificationHeader
#define HourlyPayClassificationHeader
#include "./PayClassification.h"
#include <map>
#include <ctime>

// C++ code to demonstrate the working of
// iterator, begin() and end()
#include<iostream>
#include<iterator>

namespace PayrollCaseStudy {
  namespace Classification {
class HourlyPayClassification : public PayClassification {
    public:
    float hourRate;
      std::map<std::time_t, int> timeCards;
    HourlyPayClassification(float hourRate);
    float calculatePay(time_t startPeriod, time_t endPeriod);
   void insertTimeCard(std::time_t time, int hours);
   int getTimeCard(std::time_t time);
};
  
  }
}

#endif