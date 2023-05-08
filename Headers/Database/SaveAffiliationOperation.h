#ifndef SaveAffiliationHeader
#define SaveAffiliationHeader
#include<string>

#include "./Employee.h"

#include "./sqlite3.h"

namespace PayrollCaseStudy {

  namespace PayrollEMPDB {

    class SaveAffiliationOperation {
      public:
        //Helpers Datamember for the functions
        SaveAffiliationOperation(Employee*emp, int memberId, sqlite3 * db);
      sqlite3 * DatabaseConnection;
      int memberId;
      int dues;
      int affilationId = -1;
      Employee * emp;
      void Execute();
       void CreateEmployeeMembership();
      void CreateEmployeeAffiliation();
         void   CreateAffiliation();
       private:
          std::string quotesql(const std::string & s);
    };
  }
}

#endif