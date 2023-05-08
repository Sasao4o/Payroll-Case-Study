#include "../../Headers/Transaction/PayDayTransaction.h"
 
 #include<vector>
#include<ctime>
    using namespace PayrollCaseStudy::PayrollEMPDB;
     namespace PayrollCaseStudy {

namespace TransactionBag {
 
    
    PayDayTransaction::PayDayTransaction(std::time_t date) {
        payDate = date;
    }

    void PayDayTransaction::Execute() {
        std::vector<int>ids = (PayrollDatabase::instance)->getEmployees();
        for (int i = 0; i < ids.size(); i++) {
             Employee *currentEmployee = (PayrollDatabase::instance)->getEmployee(ids[i]);
             if (currentEmployee == 0) return;
             if (currentEmployee->isPayDay(payDate)) {
                PayCheck *pc = new PayCheck(currentEmployee->getPayStartPeriod(payDate), time(0)); //hat check 7ot 3leh tare5 w paseh ll Employee hwa hy3rf y3rf hya5od kam mlk4 d3wa
                paymentRecords[currentEmployee->id] = pc; //sgl l check
                currentEmployee->payDay(pc);
             }
        
        }
    }
    PayCheck * PayDayTransaction::getPayCheck(int empId) {
               try {
                return paymentRecords.at(empId); 
             } 
             catch (std::out_of_range &e) {
                return 0;
             } 
    }
};
}
   