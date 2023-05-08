#include "../../Headers/Database/SaveTimeCardOperation.h"


namespace PayrollCaseStudy {
  namespace PayrollEMPDB {

        SaveTimeCardOperation::SaveTimeCardOperation( Employee*emp,int hours,time_t time, sqlite3*db) {
            this->emp = emp;
            this->hours = hours;
            this->time = time;
            this->DatabaseConnection = db;
        }

    void SaveTimeCardOperation::Execute() {
        CreateTimeCard();
    }

    void SaveTimeCardOperation::CreateTimeCard() {
   std::string sql;
           int rc;
        char * zErrMsg = 0;
      sql = "INSERT INTO TimeCard (Date, Hours, EmpId) VALUES (  " + std::to_string(time) + "," + std::to_string(hours) + " ," + std::to_string(emp->id) + " );";
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
      
        fprintf(stderr, "SQL ERORRRRRRRRRsRRRRRR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "INSERT INTO TimeCard Query Executed\n");
      }

    }
  
}
}