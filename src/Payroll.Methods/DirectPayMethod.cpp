#include "../../Headers/PayMethod/DirectPayMethod.h"
 
 namespace PayrollCaseStudy {
    namespace MethodsBag {
    DirectPayMethod::DirectPayMethod(std::string bankAccount, std::string account) {
        this->bankAccount = bankAccount;
        this->account = account;
    }
        void DirectPayMethod::Pay(PayCheck *pc) {
            std::cout << "I am going Payyyyyyyyyyyyyyyyyyy " << std::endl;
        }
    }
 }