#include<string>
#include<iostream>
#include "./PayMethod.h"
#ifndef DirectPayMethodHeader
#define DirectPayMethodHeader
namespace PayrollCaseStudy {
    namespace MethodsBag {
class  DirectPayMethod : public PayMethod {
    public:
    std::string bankAccount;
    std::string account;
    DirectPayMethod(std::string bankAccount, std::string account);
    void Pay(PayCheck *pc);
    };  

    }
}
    #endif