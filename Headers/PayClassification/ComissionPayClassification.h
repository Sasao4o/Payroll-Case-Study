
 #include "./PayClassification.h" 
 #ifndef ComissionPayClassificationH
#define ComissionPayClassificationH
 
 
#include <map>
#include <ctime>

// C++ code to demonstrate the working of
// iterator, begin() and end()
#include<iostream>
#include<iterator>
namespace PayrollCaseStudy {
  namespace Classification {
 
class ComissionPayClassification : public PayClassification {
    public:
    float baseRate;
    float comissionRate;
      std::map<std::time_t, float> salesReceipt;

    ComissionPayClassification(float baseRate, float comissionRate);
    
    float calculatePay(time_t startPeriod, time_t endPeriod) ;
   
    void insertSaleTransaction(std::time_t time, float amount);
    float getSaleReceipt(std::time_t time);
    
};
 
  }

}

 #endif