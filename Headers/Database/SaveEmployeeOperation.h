#ifndef SaveEmployeeHeader 
#define SaveEmployeeHeader
#include<string>
#include "./Employee.h"
#include "./sqlite3.h"
#include<string.h>
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
      
class SaveEmployeeOperation {
    public:
    //Helpers Datamember for the functions
    SaveEmployeeOperation(int id, Employee*emp, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    int id;
    std::string methodCode;
    std::string classificationCode;
    std::string insertPaymentMethodQuery;
    std::string insertClassificationQuery;
     int injectEmployeeData();
    void PreSavePaymentMethod(Employee * emp);
    void PreSaveClassificationType(Employee*emp);
    void preSaveScheduleType(Employee*emp);
    void CreateEmployee();
    void Execute();
 
    std::string getScheduleKey(PayrollCaseStudy::SchedulesBag::PaymentSchedule *paySchedule);
     std::string quotesql(const std::string & s);
};
    }
}
 

#endif