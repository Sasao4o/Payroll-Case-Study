 #include "../../Headers/Database/SaveAffiliationOperation.h"
 
 namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
  SaveAffiliationOperation::SaveAffiliationOperation(Employee*emp, int memberId, sqlite3 * db) {
                this->emp = emp;
                this->memberId = memberId;
                this->dues = emp->unionAff->getDues();
                this->DatabaseConnection = db;
    }

    void SaveAffiliationOperation::Execute() {
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
            CreateEmployeeMembership();
            CreateAffiliation();
            CreateEmployeeAffiliation();
      sqlite3_exec(DatabaseConnection, "END TRANSACTION;", NULL, NULL, NULL);
    }
void SaveAffiliationOperation::CreateEmployeeMembership() {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
             sql = "INSERT INTO EmployeeMemberShip (EmpId,MemberId) "\
      "VALUES (" + std::to_string(emp->id) + "," + std::to_string(memberId)  + ");";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
               sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }

}
void SaveAffiliationOperation::CreateEmployeeAffiliation() {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
             sql = "INSERT INTO EmployeeAffiliation (EmpId,AffiliationId) "\
      "VALUES (" + std::to_string(emp->id) + "," + std::to_string(affilationId)  + ");";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
               sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }

}

void SaveAffiliationOperation::CreateAffiliation() {
  char * zErrMsg = 0;

            int rc;
            std::string sql;
             sql = "INSERT INTO Affiliation (dues) "\
      "VALUES (" + std::to_string(dues)  + ");";
          rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
          if (rc != SQLITE_OK) {
               sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
   affilationId = sqlite3_last_insert_rowid(DatabaseConnection);
  //  std::cout << "Affiliation id " << affilationId << std::endl;
}       
    std::string SaveAffiliationOperation::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }

  }
 }