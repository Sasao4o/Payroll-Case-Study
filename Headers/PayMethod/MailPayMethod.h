#include "./PayMethod.h"
#include<string>
#include<iostream>

#ifndef MailPayMethodHeader
#define MailPayMethodHeader
namespace PayrollCaseStudy {
    namespace MethodsBag {
class MailPayMethod : public PayMethod {
    public:
    std::string mailAdress;
    MailPayMethod(std::string mailAddress);
            void Pay(PayCheck *pc);
    };  
    }
};
#endif