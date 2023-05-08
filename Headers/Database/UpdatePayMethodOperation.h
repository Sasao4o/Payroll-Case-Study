#ifndef UpdatePayMethodH 
#define UpdatePayMethodH
#include<string.h>
#include "./Employee.h"
#include "./sqlite3.h"
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
    using PayrollCaseStudy::MethodsBag::PayMethod;
class UpdatePayMethodOperation {
    public:
    UpdatePayMethodOperation( Employee*emp,PayrollCaseStudy::MethodsBag::PayMethod*payMethod, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    PayrollCaseStudy::MethodsBag::PayMethod * payMethod;
    void Execute();
    private:
      void DeleteOldMethod();
       void AddNewMethod();
    std::string insertPayMethod(PayMethod*payMethod);
     std::string quotesql(const std::string & s);
     std::string getPayMethodCode(PayMethod*payMethod);
    static int injectEmployeeData(void *data, int numberOfColumns, char** rowData, char** columnNames);  
};
    }
}
 

#endif