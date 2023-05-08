#include "./Transaction.h"
 #include "../Affiliation/UnionAffiliation.h"
  #ifndef AddServiceChargeTransHeader
  #define AddServiceChargeTransHeader
  namespace PayrollCaseStudy {

namespace TransactionBag {
class AddServiceChargeTransaction : public Transaction {
    public:
    int memberId;
    time_t time;
    int charge;
    AddServiceChargeTransaction(int memberId, time_t time, int charge);
    void Execute();
};

}
  }
  #endif