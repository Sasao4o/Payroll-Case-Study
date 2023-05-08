#ifndef UpdatePayClassH 
#define UpdatePayClassH
#include<string.h>
#include "./Employee.h"
#include "./sqlite3.h"
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::Classification::PayClassification;
class UpdatePayClassificationOperation {
    public:
    UpdatePayClassificationOperation( Employee*emp,PayrollCaseStudy::Classification::PayClassification*payClass, sqlite3*db);
    sqlite3* DatabaseConnection;
    Employee* emp;
    PayrollCaseStudy::Classification::PayClassification * payClass;
    void Execute();
    private:
      void DeleteOldClassification();
       void AddNewClassification();
    std::string insertPayClass(PayrollCaseStudy::Classification::PayClassification*payClass);
     std::string quotesql(const std::string & s);
    static int injectEmployeeData(void *data, int numberOfColumns, char** rowData, char** columnNames);  
};
    }
}
 

#endif