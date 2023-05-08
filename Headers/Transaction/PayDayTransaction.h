#include "./Transaction.h"
 
 #include<vector>
#include<ctime>
    using namespace PayrollCaseStudy::PayrollEMPDB;
     namespace PayrollCaseStudy {

namespace TransactionBag {
class PayDayTransaction : public Transaction {
    public:
    std::time_t payDate;
    std::map<int, PayCheck*> paymentRecords; //de  momken y7slha print msln w tslmha l moder l far3
    PayDayTransaction(std::time_t date);

    void Execute();
    PayCheck * getPayCheck(int empId);
};
}
     }