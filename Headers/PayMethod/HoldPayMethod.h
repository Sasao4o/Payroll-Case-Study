 
#include<iostream>
#include "../../Headers/PayMethod/PayMethod.h"
#include<string>
#ifndef HoldPayMethodHeader
#define HoldPayMethodHeader
namespace PayrollCaseStudy {
    namespace MethodsBag {
class HoldPayMethod : public PayMethod {
        void Pay(PayCheck *pc);
    };  

    }
};

#endif