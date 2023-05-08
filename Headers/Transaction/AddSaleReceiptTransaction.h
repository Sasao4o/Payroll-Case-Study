 #ifndef AddSaleReceiptTransactionHeader
#define AddSaleReceiptTransactionHeader
#include "./Transaction.h"
#include "../PayClassification/ComissionPayClassification.h"
#include <ctime>
  namespace PayrollCaseStudy {

namespace TransactionBag {
class AddSaleReceiptTransaction : public Transaction {
    public:
    int employeeId;
    std::time_t time;
    int amount;
    AddSaleReceiptTransaction(int id,std::time_t time, int amount);
    void Execute();

};
}
  }
#endif