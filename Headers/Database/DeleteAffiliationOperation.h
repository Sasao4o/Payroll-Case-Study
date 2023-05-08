#ifndef DeleteAffiliationHeader
#define DeleteAffiliationHeader
 
#include "./Employee.h"

#include "./sqlite3.h"
#include<string.h>
namespace PayrollCaseStudy {

  namespace PayrollEMPDB {

    class DeleteAffiliationOperation {
      public:
        //Helpers Datamember for the functions
        DeleteAffiliationOperation( int empId, int memberId, sqlite3 * db);
      sqlite3 * DatabaseConnection;
      int memberId;
      
      int affilationId = -1;
      int empId = -1;
      Employee * emp;
      void Execute();
       void DeleteEmployeeMemberShip();
      void DeleteEmployeeAffiliation();
         void   DeleteAffiliation(int affId);
         void DeleteServiceCharges(int affId);
       private:
         int   getAffiliationId();
          std::string quotesql(const std::string & s);
            static int injectAffiliationId(void *data, int numberOfColumns, char** rowData, char** columnNames);
    };
  }
}

#endif