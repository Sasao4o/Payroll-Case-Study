#include "../../Headers/PayMethod/MailPayMethod.h"
 //Hwa m4 m722 l pay leh mtl34 error?
 namespace PayrollCaseStudy {
    namespace MethodsBag {
    MailPayMethod::MailPayMethod(std::string mailAddress) {
        this->mailAdress = mailAddress;
    }
        void MailPayMethod::Pay(PayCheck *pc) {
            std::cout << "I am going Payyyyyyyyyyyyyyyyyyy " << std::endl;
        }
    }
 }