  #ifndef PayMethodHeader
 #define PayMethodHeader
#include "../PayrollPay/PayCheck.h"
namespace PayrollCaseStudy {
    namespace MethodsBag {
class PayMethod {
    public:
     virtual void Pay(PayCheck* pc) = 0;
};
    }
}
 #endif