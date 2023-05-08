#ifndef SaveSaleReceiptH 
#define SaveSaleReceiptH
#include<string.h>
#include "./Employee.h"
#include "./sqlite3.h"
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
      
class SaveSaleReceiptOperation {
    public:
    //Helpers Datamember for the functions
    SaveSaleReceiptOperation( Employee*emp,float amount,time_t time, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    time_t time;
    float amount;
    void Execute();
  
    private:
     std::string quotesql(const std::string & s);
     void CreateSaleReceipt();
};
    }
}
 

#endif