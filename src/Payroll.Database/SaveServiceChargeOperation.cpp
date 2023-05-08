#include "../../Headers/Database/SaveServiceChargeOperation.h"


namespace PayrollCaseStudy {
  namespace PayrollEMPDB {

        SaveServiceChargeOperation::SaveServiceChargeOperation( Employee*emp,int charge,time_t time, sqlite3*db) {
            this->emp = emp;
            this->charge = charge;
            this->time = time;
            this->DatabaseConnection = db;
        }

    void SaveServiceChargeOperation::Execute() {
        int affiliationId = LoadEmployeeAffiliation();
        // std::cout << "AffiliationId is " << affiliationId << std::endl;
        if (affiliationId == -1) return;
        CreateServiceCharge(affiliationId);
    }


 
    int SaveServiceChargeOperation::LoadEmployeeAffiliation() {
    std::string sql;
           int rc;
           char * zErrMsg = 0;
            int result = -1;
       sql = "SELECT * FROM EmployeeAffiliation WHERE EmpId =" + std::to_string(emp->id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectAffiliationId, &result, & zErrMsg);
        return result;
  }

int SaveServiceChargeOperation::injectAffiliationId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      int * affiliationId = static_cast < int * > (data);
      int returnedAff = -1;
   
          for (int i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "AffiliationId")) {
          returnedAff = atoi(rowData[i]);
        }  
      }
    (*affiliationId) = returnedAff;
     return 0;
  }
   void SaveServiceChargeOperation::CreateServiceCharge(int affiliationId) {
   
      std::string sql;
           int rc;
        char * zErrMsg = 0;
         
      sql = "INSERT INTO ServiceCharge (Date, Amount, AffiliationId) VALUES (  " + std::to_string(time) + "," + std::to_string(charge) + " ," + std::to_string(affiliationId) + " );";
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
      
        fprintf(stderr, "SQL ERORRRRRRRRRsRRRRRR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "INSERT INTO ServiceCharge Query Executed\n");
      }
   }
}
}