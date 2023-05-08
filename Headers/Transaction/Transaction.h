#ifndef TransactionHeader
#define TransactionHeader
#include<map>
#include "../Database/Employee.h"
#include "../Database/PayrollDatabase.h"
namespace PayrollCaseStudy {

namespace TransactionBag {
class Transaction {
    public:
    void virtual Execute() = 0;
};


}
}
#endif