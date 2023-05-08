#include "../../Headers/Database/SaveSaleReceiptOperation.h"


namespace PayrollCaseStudy {
  namespace PayrollEMPDB {

        SaveSaleReceiptOperation::SaveSaleReceiptOperation( Employee*emp,float amount,time_t time, sqlite3*db) {
            this->emp = emp;
            this->amount = amount;
            this->time = time;
            this->DatabaseConnection = db;
        }

     void SaveSaleReceiptOperation::Execute() {
        CreateSaleReceipt();
    }

    void SaveSaleReceiptOperation::CreateSaleReceipt() {
   std::string sql;
           int rc;
        char * zErrMsg = 0;
      // sql = "INSERT INTO SaleReceipt (Date, Amount, EmpId) VALUES ( DATE( " + std::to_string(time) + ", 'unixepoch'), " + std::to_string(amount) + " ," + std::to_string(emp->id) + " );";
            sql = "INSERT INTO SaleReceipt (Date, Amount, EmpId) VALUES (" + std::to_string(time) + "," + std::to_string(amount) + " ," + std::to_string(emp->id) + " );";

      
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
      
        fprintf(stderr, "SQL ERORRRRRRRRRsRRRRRR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "INSERT INTO SaleReceipt Query Executed\n");
      }

    }

 
    
}
}