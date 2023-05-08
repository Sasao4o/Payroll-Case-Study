#ifndef SaveServiceChargeH 
#define SaveServiceChargeH
#include<string.h>
#include "./Employee.h"
#include "./sqlite3.h"
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
      
class SaveServiceChargeOperation {
    public:
    //Helpers Datamember for the functions
    SaveServiceChargeOperation( Employee*emp,int charge,time_t time, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    time_t time;
    int charge;
    void Execute();
    int LoadEmployeeAffiliation();
    void CreateServiceCharge(int);
    private:
     std::string quotesql(const std::string & s);
     static int injectAffiliationId(void * data, int numberOfColumns, char ** rowData, char ** columnNames);
};
    }
}
 

#endif