 #include "../../Headers/Database/DeleteAffiliationOperation.h"
 
 namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
  DeleteAffiliationOperation::DeleteAffiliationOperation(int empId,  int memberId, sqlite3 * db) {
                this->memberId = memberId;
                this->DatabaseConnection = db;
                this->empId = empId;
    }

    void DeleteAffiliationOperation::Execute() {

     int rc;
      char * zErrMsg = 0;
    rc = sqlite3_exec(DatabaseConnection, "BEGIN TRANSACTION;", NULL, NULL, & zErrMsg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: Transaction Failed %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return;
      } else {
        fprintf(stdout, "Executing Transaction.....\n");
      }
      int affId =  getAffiliationId();
 
            DeleteEmployeeMemberShip();
     
       DeleteEmployeeAffiliation();
            DeleteAffiliation(affId);
          DeleteServiceCharges(affId);
      sqlite3_exec(DatabaseConnection, "END TRANSACTION;", NULL, NULL, NULL);
    }
   


   void DeleteAffiliationOperation::DeleteEmployeeMemberShip() {
  char * zErrMsg = 0;

            int rc;
            std::string sql;

             sql = "DELETE FROM EmployeeMemberShip   WHERE MemberId =" + std::to_string(memberId) + ";";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
                  fprintf(stderr, "SQL error: %s\n", zErrMsg);
               sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
     
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
    
   }
     int DeleteAffiliationOperation::getAffiliationId() {
            std::string sql;
      char * zErrMsg = 0;
      int rc;
      int affId;
      sql = "SELECT * FROM EmployeeAffiliation WHERE EmpId = " + std::to_string(empId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectAffiliationId, & affId, & zErrMsg);
      return affId;
     }
 void DeleteAffiliationOperation::DeleteEmployeeAffiliation() {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
             sql = "DELETE FROM EmployeeAffiliation  WHERE EmpId =" + std::to_string(empId) + ";";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
             
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
             sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
    
   }
 void DeleteAffiliationOperation::DeleteAffiliation(int affId) {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
     
             sql = "DELETE FROM Affiliation  WHERE AffiliationId =" + std::to_string(affId) + ";";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
   
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
                       sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
    
   }

    void DeleteAffiliationOperation::DeleteServiceCharges(int affId) {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
             sql = "DELETE FROM ServiceCharge  WHERE AffiliationId =" + std::to_string(affId) + ";";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
               sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
    
   }
    std::string DeleteAffiliationOperation::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }
 int DeleteAffiliationOperation::injectAffiliationId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
       int * aff = static_cast < int * > (data);
      int i;
      int affId = -1;
 
      for (i = 0; i < numberOfColumns; i++) {
           
        if (!strcmp(columnNames[i], "AffiliationId")) {
            affId = atoi(rowData[i]);

        }  
     
      }   
   *aff = affId;
      return 0;
      printf("\n");
      return 0;
    }
  }
 }