#include "../../Headers/Database/Employee.h"
 
// #include "../Payroll.Classification/PayClassification.cpp"
// #include "../Payroll.Methods/PayMethod.cpp"
 
// #include "../Payroll.Affiliation/Affiliation.cpp"
// #include "../Payroll.Schedules/PaymentSchedule.cpp"
// #include "../Payroll.Pay/PayCheck.cpp"
using namespace PayrollCaseStudy::Classification;
using namespace PayrollCaseStudy::AffiliationBag;
using namespace PayrollCaseStudy::MethodsBag;
using namespace PayrollCaseStudy::SchedulesBag;
 namespace PayrollCaseStudy {
    namespace PayrollEMPDB {
PayClassification* Employee::getPaymentClassification() {
    return this->pay;
}

 
    void Employee::setUnionAff(Affiliation *unionAff) {
            this->unionAff = unionAff;
    };
    void Employee::setName(std::string name) {
        this->name = name;
    };
    void Employee::setAge(int age) {
        this->age = age;
    };
    void Employee::setEmail(std::string email) {
    this->email = email;
    };
    void Employee::setPayClass(PayClassification *payClass) {
        this->pay = payClass;
    };
    void Employee::setPayMethod(PayMethod *payMethod) {
        this->payMethod = payMethod;
    };
    
        void Employee::setPaySchedule(PaymentSchedule *ps) {
        this->paySchedule = ps;
    }; 

        bool Employee::isPayDay(time_t payDate) {
            if (paySchedule == 0) return 0;
                return paySchedule->isPayDate(payDate);
        }
        void Employee::payDay(PayCheck *pc) {
            
            float grossPay = (this->pay)->calculatePay(pc->startDate, pc->endDate);
            float netPay = grossPay;
                          
            // if (this->unionAff != 0) { // l null pattern y7llk l 5ra da
            float deductions = (this->unionAff)->calculateDeductions(pc->startDate, pc->endDate);
             netPay = grossPay - deductions;
            pc->deductions = deductions;    
            // }
            pc->grossPay = grossPay;
            pc->netPay = netPay;
            payMethod->Pay(pc);
        }

    std::time_t Employee::getPayStartPeriod(std::time_t payDate) {
           return paySchedule->getPayStartPeriod(payDate);
    }
    }
 }