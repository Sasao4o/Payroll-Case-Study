 
 #ifndef AddTimeCardTransactionHeader
#define AddTimeCardTransactionHeader
 #include "./Transaction.h"
 
#include <ctime>
 namespace PayrollCaseStudy {

namespace TransactionBag {
class AddTimeCardTransaction : public Transaction {
    public:
    int employeeId;
    std::time_t time;
    int hours;
    AddTimeCardTransaction(int id,std::time_t time, int hours);
    void Execute();

};
}
 }
#endif