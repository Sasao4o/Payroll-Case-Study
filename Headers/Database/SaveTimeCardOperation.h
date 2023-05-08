#ifndef SaveTimeCardH 
#define SaveTimeCardH
#include<string.h>
#include "./Employee.h"
#include "./sqlite3.h"
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
      
class SaveTimeCardOperation {
    public:
    //Helpers Datamember for the functions
    SaveTimeCardOperation( Employee*emp,int hours,time_t time, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    time_t time;
    int hours;
    void Execute();
    void CreateTimeCard();
    private:
     std::string quotesql(const std::string & s);
      
};
    }
}
 

#endif