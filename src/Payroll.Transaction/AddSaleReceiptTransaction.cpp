 

    #include "../../Headers/Transaction/AddSaleReceiptTransaction.h"
 
         using namespace PayrollCaseStudy::PayrollEMPDB;
          namespace PayrollCaseStudy {

namespace TransactionBag {
    using PayrollCaseStudy::Classification::ComissionPayClassification;
    AddSaleReceiptTransaction::AddSaleReceiptTransaction(int id,std::time_t time, int amount) {
        this->employeeId = id;
              this->time = time;
                    this->amount = amount;
    }
    void AddSaleReceiptTransaction::Execute() {
             
         Employee *myEmployee = (PayrollDatabase::instance)->getEmployee(employeeId);
               std::cout << "INSERTION B4 BE DONE BBY" << employeeId;
            if (myEmployee == 0) {
                return;
            }
                    std::cout << "INSERTION DONE BBY";
            if (myEmployee->getPaymentClassification() == 0) {
                return;
            }
            
            ComissionPayClassification *payClass =   dynamic_cast<ComissionPayClassification *>(myEmployee->getPaymentClassification());
           
            if (payClass == nullptr) return;
            payClass->insertSaleTransaction(time,amount);
            (PayrollCaseStudy::PayrollEMPDB::PayrollDatabase::instance)->AddSaleReceipt(myEmployee, time, amount);
            // payClass->insertTimeCard();
            std::cout << "INSERTION DONE BBY";
    }   

}
          }