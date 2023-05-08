
#include "../../Headers/PayClassification/HourlyPayClassification.h"

 namespace PayrollCaseStudy {
  namespace Classification {


    HourlyPayClassification::HourlyPayClassification(float hourRate) {
        this->hourRate = hourRate;
    }
    float HourlyPayClassification::calculatePay(time_t startPeriod, time_t endPeriod) {
             std::map<std::time_t, int>::iterator it;
            int totalHours = 0;
            int totalPay = 0;
        for (it = timeCards.begin(); it != timeCards.end(); it++)
        {
        
            if (!isInPayPeriod(it->first,  startPeriod,  endPeriod)) continue;
            totalHours = it->second;
             if (totalHours > 8) {
                totalPay += ((totalHours - 8) * 1.5 * hourRate) + (8 * hourRate);
                } else {
                     
                    totalPay += totalHours * hourRate;
                }
           
        }
  
        return totalPay;

    }
    void HourlyPayClassification::insertTimeCard(std::time_t time, int hours) {
            timeCards[time] = hours;
    }
        bool isPayDate(std::time_t payDate)
    {
        return  true;
    }
      int HourlyPayClassification::getTimeCard(std::time_t time) {
            int amount;
          try {
               amount =  this->timeCards.at(time); 
             } 
             catch (std::out_of_range &e) {
               amount = -1;
             } 
             return amount;
      }
  }
 }

