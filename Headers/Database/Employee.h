 
#include "../Affiliation/Affiliation.h"
 
#include "../Affiliation/NoAffiliation.h"
 #include "../PaySchedule/PaymentSchedule.h"
  #include "../PayMethod/PayMethod.h"
 #include "../PayClassification/PayClassification.h"
 
#ifndef EmployeeHeader
#define EmployeeHeader
#include<iostream>
#include<string>
 
#include<ctime>
 namespace PayrollCaseStudy {
    namespace PayrollEMPDB {
class Employee {
    public:
    int id;
    std::string name;
    int age;
    std::string email;
    std::string address;
    PayrollCaseStudy::Classification::PayClassification *pay = 0;
    PayrollCaseStudy::MethodsBag::PayMethod *payMethod = 0;
    PayrollCaseStudy::SchedulesBag::PaymentSchedule *paySchedule = 0;
    PayrollCaseStudy::AffiliationBag::Affiliation *unionAff = 0; //Not mandatory so won't be in constructor
    Employee(int id,std::string name, std::string email, int age, std::string address, PayrollCaseStudy::Classification::PayClassification *pay, PayrollCaseStudy::MethodsBag::PayMethod *payMethod) {
        this->name = name;
        this->age = age;
        this->email = email;
        this->pay = pay;
        this->payMethod = payMethod;
        this->id = id;
        this->address = address;
        unionAff = new   PayrollCaseStudy::AffiliationBag::NoAffiliation();
    }
    PayrollCaseStudy::Classification::PayClassification* getPaymentClassification();
    void setUnionAff(PayrollCaseStudy::AffiliationBag::Affiliation *unionAff);
    void setName(std::string name);
    void setAge(int age);
    void setEmail(std::string email);
    void setPayClass(PayrollCaseStudy::Classification::PayClassification *payClass);
    void setPayMethod(PayrollCaseStudy::MethodsBag::PayMethod *payClass);
    void setPaySchedule(PayrollCaseStudy::SchedulesBag::PaymentSchedule *paySchedule);
    bool isPayDay(std::time_t payDate);
    void payDay(PayCheck *pc);
    std::time_t getPayStartPeriod(std::time_t payDate);
}; 

 
 }
 }

 #endif