 
#include "../../Headers/PayClassification/ComissionPayClassification.h"

 namespace PayrollCaseStudy {
  namespace Classification {

    ComissionPayClassification::ComissionPayClassification(float baseRate, float comissionRate) {
        this->baseRate = baseRate;
         this->comissionRate = comissionRate;
    }
   float ComissionPayClassification::calculatePay(time_t startPeriod, time_t endPeriod) {
             std::map<std::time_t, float>::iterator it;
     
            float totalPay = 0;
        for (it = salesReceipt.begin(); it != salesReceipt.end(); it++)
        {
            if (!isInPayPeriod(it->first,  startPeriod,  endPeriod)) continue;
            totalPay += (comissionRate) * it->second;
        }
      
        return totalPay + baseRate;

    }
void ComissionPayClassification::insertSaleTransaction(std::time_t time, float amount) {
            salesReceipt[time] = amount;
    }
float ComissionPayClassification::getSaleReceipt(std::time_t time) {
    float amount;
          try {
               amount =  this->salesReceipt.at(time); 
             } 
             catch (std::out_of_range &e) {
               amount = -1;
             } 
             return amount;
    }
  }
 }