#include "./Transaction.h"
      namespace PayrollCaseStudy {

namespace TransactionBag {
class DeleteEmployeeTransaction : public Transaction {
    public:
    int employeeId;
    DeleteEmployeeTransaction(int id);
    void Execute();

};
}
      }