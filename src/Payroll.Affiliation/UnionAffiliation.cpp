 
#include <map>
#include <ctime>
#include<math.h>
#include "../../Headers/Affiliation/UnionAffiliation.h"
 namespace PayrollCaseStudy {
    namespace AffiliationBag {
 
    UnionAffiliation::UnionAffiliation(int memberId, int weeklyDues) {
        this->memberId = memberId;
        this->weeklyDues = weeklyDues;

    }
    int UnionAffiliation::getServiceCharge(time_t timeC) {
          int amount;
          try {
               amount =  this->serviceCharge.at(timeC); 
             } 
             catch (std::out_of_range &e) {
               amount = -1;
             } 
             return amount;
    }
           int UnionAffiliation::getDues() {
            return weeklyDues;
    }
    void UnionAffiliation::addServiceCharge(time_t time, int charge) {
        serviceCharge[time] = charge;
    }
    float UnionAffiliation::calculateDeductions(time_t startPeriod, time_t endPeriod) {
 
          //company policy l abd 3n 28 mlk4 d3wa :D 
        float daysDiff = std::difftime(endPeriod, startPeriod) / (60 * 60 * 24);

        int weeksDiff = floor(daysDiff / 5.0);
      // std::cout << "WeeksDif are " << weeksDiff << std::endl;
          float accWeeklyDues = weeksDiff * weeklyDues;

               std::map<std::time_t, int>::iterator it;
    int accServiceChage = 0;
        for (it = serviceCharge.begin(); it != serviceCharge.end(); it++)
        {
            if (!isInPayPeriod(it->first,  startPeriod,  endPeriod)) continue;
            accServiceChage += it->second;
        }   
      // std::cout << "DEDCUTIONS ARE " << accServiceChage << "And " << accWeeklyDues << std::endl;
    return accServiceChage + accWeeklyDues;
    }
    }
 }