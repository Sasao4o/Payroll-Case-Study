#include "../../Headers/Database/SqlDb.h"
 

//THIS SHOWS WE Have OCP Violation as we depends on impelementation
#include "../../Headers/PayClassification/ComissionPayClassification.h"

#include "../../Headers/PayClassification/HourlyPayClassification.h"

#include "../../Headers/PayClassification/MonthlyPayClassification.h"

#include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"

#include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"


#include "../../Headers/PayMethod/DirectPayMethod.h"

#include "../../Headers/PayMethod/HoldPayMethod.h"

#include "../../Headers/PayMethod/MailPayMethod.h"

// END
 
namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
    using PayrollCaseStudy::MethodsBag::PayMethod;
    using PayrollCaseStudy::Classification::PayClassification;
    using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
    SqlDb::SqlDb() {
  
      char * zErrMsg = 0;
      int rc;
      //Open PayrollDB and create if it doesn't exists
      rc = sqlite3_open("payrollDb.db", & DatabaseConnection);
      
      if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DatabaseConnection));

      } else {
        fprintf(stderr, "Opened database successfully\n");
      }
      std::string enableForeignKey = "PRAGMA foreign_keys = ON;";
      rc = sqlite3_exec(DatabaseConnection, enableForeignKey.c_str(), 0, 0, & zErrMsg);


      if (rc) {
        fprintf(stderr, "Can't open database: With Foreign Key Constraints%s\n", sqlite3_errmsg(DatabaseConnection));

      } else {
        fprintf(stderr, "Opened database successfully\n");
      }
      char * sql;

      sql = "CREATE TABLE IF NOT EXISTS Employee("\
      "EmpId INTEGER PRIMARY KEY AUTOINCREMENT,"\
      "Name           TEXT    NOT NULL,"\
      "Email           TEXT    NOT NULL UNIQUE,"\
      "Age           INT    NOT NULL,"\
      "Address            TEXT     NOT NULL,"\
      "ScheduleType        TEXT NOT NULL,"\
      "PaymentMethodType         TEXT NOT NULL,"\
      " PaymentClassificationType    TEXT NOT NULL );";
      /* Execute SQL statement */
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS HourlyClassification("\
      "EmpId INT PRIMARY KEY     NOT NULL ,"\
      "HourlyRate           REAL    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE );";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS SalaryClassification("\
      "EmpId INT PRIMARY KEY     NOT NULL ,"\
      "Salary           REAL    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE);";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS CommissionClassification("\
      "EmpId INT PRIMARY KEY     NOT NULL ,"\
      "Salary           REAL    NOT NULL,"\
      "Commission  REAL NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE);";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS Affiliation("\
      "AffiliationId INTEGER PRIMARY KEY AUTOINCREMENT ,"\
      "Dues          REAL    NOT NULL);";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS EmployeeAffiliation("\
      "EmpId INT PRIMARY KEY     NOT NULL ,"\
      "AffiliationId           INT    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "FOREIGN KEY(AffiliationId) REFERENCES Affiliation(AffiliationId) ON DELETE CASCADE);";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS ServiceCharge("\
      "Date INT      NOT NULL ,"\
      "Amount           REAL    NOT NULL,"\
      "AffiliationId           INT    NOT NULL,"\
      "FOREIGN KEY(AffiliationId) REFERENCES Affiliation(AffiliationId) ON DELETE CASCADE,"\
      "PRIMARY KEY(AffiliationId, Date));";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS SaleReceipt("\
      "Date INT      NOT NULL ,"\
      "Amount           REAL    NOT NULL,"\
      "EmpId           INT    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "PRIMARY KEY(EmpId, Date));";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS TimeCard("\
      "Date INT      NOT NULL ,"\
      "Hours           REAL    NOT NULL,"\
      "EmpId           INT    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "PRIMARY KEY(EmpId, Date));";
      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS DirectDepositAccount("\
      "Bank TEXT      NOT NULL ,"\
      "Account           TEXT    UNIQUE NOT NULL,"\
      "EmpId           INT   NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "CHECK(Bank <> '')"\
      "CHECK(Account <> '')"\
      "PRIMARY KEY(EmpId));";

      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }

      sql = "CREATE TABLE IF NOT EXISTS PayCheckAddress("\
      "Address TEXT      NOT NULL ,"\
      "EmpId           INT    NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "PRIMARY KEY(EmpId));";

      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }
   

      sql = "CREATE TABLE IF NOT EXISTS EmployeeMemberShip("\
      "MemberId INT      NOT NULL ,"\
      "EmpId           INT    UNIQUE NOT NULL,"\
      "FOREIGN KEY(EmpId) REFERENCES Employee(EmpId) ON DELETE CASCADE,"\
      "PRIMARY KEY(MemberId));";

      rc = sqlite3_exec(DatabaseConnection, sql, 0, 0, & zErrMsg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Table created successfully\n");
      }
    }

    void SqlDb::AddEmployee(int id, Employee * emp) {
      SaveEmployeeOperation * saveProcess = new SaveEmployeeOperation(id, emp, DatabaseConnection);
      saveProcess->Execute();
     

    }
    Employee * SqlDb::getEmployee(int id) {
      LoadEmployeeOperation *loadProcess = new LoadEmployeeOperation(id, DatabaseConnection);
      loadProcess->Execute();
      return loadProcess->getEmployee();
 
      //note this operator may lead to unexpected behaviour as it creats the object using default constructor if it doesn;t find it
      // sqlite3 * db;
      // char * zErrMsg = 0;
      // int rc;
      // //Open PayrollDB and create if it doesn't exists
      // rc = sqlite3_open("payrollDb.db", & db);
      //       std::string enableForeignKey = "PRAGMA foreign_keys = ON;";
      // rc = sqlite3_exec(db, enableForeignKey.c_str(), 0, 0, & zErrMsg);
      // if (rc) {
      //   fprintf(stderr, "Can't open database: With Foreign Key Constraints%s\n", sqlite3_errmsg(db));

      // } else {
      //   fprintf(stderr, "Opened database successfully\n");
      // }
      // if (rc) {
      //   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      //   return 0;
      // } else {
      //   fprintf(stderr, "Opened database successfully\n");
      // }
      // std::string sql;

      // sql = "SELECT * FROM Employee WHERE EmpId =" + std::to_string(id) + ";";
      // Employee * returnedEmp = 0;
      // // struct EmployeeRecord {
      // //     int empId;
      // //     std::string name;
      // //     std::string adddress;
      // //     std::string email;
      // //     int address;
      // //     int age;
      // //     std::string ScheduleType;
      // //     std::string PaymentMethodType;
      // //     std::string PaymentClassificationType;
      // // } empRecord;
      // /*  Execute SQL statement */
      // rc = sqlite3_exec(db, sql.c_str(), injectEmployeeData, returnedEmp, & zErrMsg);
      // if (rc != SQLITE_OK) {
      //   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      //   sqlite3_free(zErrMsg);
      // } else {
      //   fprintf(stdout, "GET Query Executed\n");
      // }
   

       return 0;
    }

    void SqlDb::AddUnionMember(int memberId, Employee * emp) {
      SaveAffiliationOperation *saveAffProcess = new SaveAffiliationOperation(emp, memberId, DatabaseConnection);
      saveAffProcess->Execute();
    }
    int SqlDb::getUnionMember(int memberId) {
      std::string sql;
      char * zErrMsg = 0;
      int rc;
      int empId = -1;
      sql = "SELECT * FROM EmployeeMemberShip WHERE MemberId = " + std::to_string(memberId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectEmployeeId, & empId, & zErrMsg);
      return empId;
    }
    std::vector < int > SqlDb::getEmployees() {
      std::vector<int> ids;
           std::string sql;
      char * zErrMsg = 0;
      int rc;
      sql = "SELECT EmpId from Employee";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectEmployeesId, & ids, & zErrMsg);
       if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Query Executed\n");
      }
      return ids;
    }
    void SqlDb::DeleteUnionMember(int memberId) {
      int empId = getUnionMember(memberId);
      if (empId == -1) return;
   DeleteAffiliationOperation *deleteAffProcess = new DeleteAffiliationOperation(empId, memberId, DatabaseConnection);
      deleteAffProcess->Execute();
    }
    void SqlDb::DeleteEmployee(int id) {
      char * zErrMsg = 0;
      int rc;
      std::string sql;
      sql = "DELETE FROM Employee WHERE EmpId = " + std::to_string(id) + ";";
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Query Executed\n");
      }
    }

      void SqlDb::UpdateEmployee(int id, std::string key, std::string value) {
      char * zErrMsg = 0;
      int rc;
      std::string sql;
      sql = "UPDATE Employee SET " + key + "=" + quotesql(value)  + " WHERE EmpId = " + std::to_string(id) + ";";
 
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Query Executed\n");
      }
    }
    std::string SqlDb::getScheduleKey(PaymentSchedule * paySchedule) {
      //This depends on the implementation and violates OCP heavilyyy
      if (dynamic_cast < PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule * > (paySchedule) != nullptr) {
        return "weekly";

      }
      if (dynamic_cast < PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule * > (paySchedule) != nullptr) {
        return "monthly";
      }

      return "unknwon";
    }

    std::string SqlDb::getPayClassificationKey(PayClassification * payClass) {
      if (dynamic_cast < PayrollCaseStudy::Classification::ComissionPayClassification * > (payClass) != nullptr) {
        return "comission";

      }
      if (dynamic_cast < PayrollCaseStudy::Classification::HourlyPayClassification * > (payClass) != nullptr) {
        return "hourly";
      }
      if (dynamic_cast < PayrollCaseStudy::Classification::MonthlyPayClassification * > (payClass) != nullptr) {
        return "monthly";
      }

      return "unknwon";
    }
    std::string SqlDb::getPayMethodKey(PayMethod * payMethod) {
      if (dynamic_cast < PayrollCaseStudy::MethodsBag::DirectPayMethod * > (payMethod) != nullptr) {
        return "direct";

      }
      if (dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (payMethod) != nullptr) {
        return "mail";
      }
      return "unknwon";
    }

    std::string SqlDb::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }
   
    void SqlDb::AddSerivceCharge(Employee*emp, time_t time, int charge) {
  
     SaveServiceChargeOperation* saveService = new SaveServiceChargeOperation(emp, charge, time, DatabaseConnection);
     saveService->Execute();

    }

      void SqlDb::AddTimeCard(Employee*emp, time_t time, int hours) {
      SaveTimeCardOperation* saveService = new SaveTimeCardOperation(emp, hours, time, DatabaseConnection);
     saveService->Execute();

    }
    void SqlDb::AddSaleReceipt(Employee *emp, time_t time, float amount) {
            SaveSaleReceiptOperation* saveSaleReceipt = new SaveSaleReceiptOperation(emp, amount, time, DatabaseConnection);
     saveSaleReceipt->Execute();
    }
        void SqlDb::UpdateEmpPayMethod(int id, PayMethod *payMethod) {
        UpdatePayMethodOperation*updatePayMethodOperation = new UpdatePayMethodOperation(getEmployee(id), payMethod, DatabaseConnection);
        updatePayMethodOperation->Execute();

    }

      void SqlDb::UpdateEmpPayClass(int id, PayClassification *payClass) {
        UpdatePayClassificationOperation*updatePayMethodOperation = new UpdatePayClassificationOperation(getEmployee(id), payClass, DatabaseConnection);
        updatePayMethodOperation->Execute();

    }
    void SqlDb::ClearDatabase() {

 
    if (DatabaseConnection == 0) return;
    int rc;
    std::string sql;
    char * zErrMsg = 0;
    sql = "DELETE FROM DirectDepositAccount";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
   sql = "DELETE FROM PayCheckAddress";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM EmployeeMemberShip";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM EmployeeAffiliation";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted from EmployeeAff successfully\n");
    }
    sql = "DELETE  FROM ServiceCharge";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
    sql = "DELETE  FROM Affiliation";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error in Affiliation%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM SalaryClassification";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
    sql = "DELETE FROM HourlyClassification";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM CommissionClassification";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM TimeCard";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM SaleReceipt";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }

    sql = "DELETE FROM Employee";
    rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(DatabaseConnection));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }

    }
    // int SqlDb::injectEmployeeData(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
    //   // EmployeeRecord * emp = static_cast < Employee * > (data);
    //   int i;
    //   int empId = -1;
    //   std::string name;
    //   std::string email;
    //   int age;
    //   std::string address;
    //    std::string ScheduleType;
    //   std::string PaymentMethodType;
    //  std::string PaymentClassificationType;
    //   for (i = 0; i < numberOfColumns; i++) {
    //       std::cout << std::endl << "Column name is" << columnNames[i] <<  "Row Data is " << rowData[i] << std::endl;
    //     if (!strcmp(columnNames[i], "EmpId")) {
    //         empId = atoi(rowData[i]);

    //     } else if (!strcmp(columnNames[i], "Name")) {
         
    //         name = rowData[i];
    //     } else if (!strcmp(columnNames[i], "Email")) {
    //               email = rowData[i];

    //     } else if (!strcmp(columnNames[i], "Age")) {
    //        age = atoi(rowData[i]);

    //     } else if (!strcmp(columnNames[i], "Address")) {
    //          address = rowData[i];

    //     } else if (!strcmp(columnNames[i], "ScheduleType")) {

    //             // fetchScheduleType(rowData[i], empId)
    //          ScheduleType = rowData[i];
         
    //     } else if (!strcmp(columnNames[i], "PaymentMethodType")) {
    //        PaymentMethodType = rowData[i];
         
    //     } else if (!strcmp(columnNames[i], "PaymentClassificationType")) {
 
    //              PaymentClassificationType = rowData[i];
    //     } else {
    //       std::cout << "ERRRRORRRRR";
    //     }
    
    //   }   
 
    //   printf("\n");
    //   return 0;
    // }
    //     void SqlDb::preSaveScheduleType(Employee * emp, int rc) {
    //   //This depends on the implementation and violates OCP heavilyyy
    //   //this method violates single responsiplity as it put in the methodCode to be inserted in employee table
    //   //and also insert in payment related table but it has very good attuide as it is concentrated not spreaded!

    //   if (dynamic_cast < PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule * > (emp->paySchedule) != nullptr) {
    //     scheduleCode =  "weekly";

    //   }
    //   if (dynamic_cast < PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule * > (emp->paySchedule) != nullptr) {
    //     scheduleCode =  "monthly";
    //   }

    // }
         void SqlDb::UpdateEmpPaySchedule(int id, PayrollCaseStudy::SchedulesBag::PaymentSchedule*paySchedule) {
          std::string sql;
          char * zErrMsg = 0;
          int rc;
          std::string scheduleCode;
      if (dynamic_cast < PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule * > (paySchedule) != nullptr) {
        scheduleCode = "weekly";
      }
      else if (dynamic_cast < PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule * > (paySchedule) != nullptr) {
        scheduleCode =  "monthly";
      }

    sql = "UPDATE Employee SET ScheduleType =" + quotesql(scheduleCode) + "WHERE EmpId = " +  std::to_string(id) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
         if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Update Employee ScheduleType Query Executed\n");
        }

    }


 int SqlDb::injectEmployeeId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
       int * emp = static_cast < int * > (data);
      int i;
      int empId = -1;
 
      for (i = 0; i < numberOfColumns; i++) {
        
        if (!strcmp(columnNames[i], "EmpId")) {
            empId = atoi(rowData[i]);
        }  
      }   
        *emp = empId;
      return 0;
      printf("\n");
      return 0;
    }

     int SqlDb::injectEmployeesId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
       std::vector<int>*  ids = static_cast < std::vector<int>* > (data);
      int i;
      int empId = -1;
 
      for (i = 0; i < numberOfColumns; i++) {
        
        if (!strcmp(columnNames[i], "EmpId")) {
            empId = atoi(rowData[i]);
        }  
      }   
      if (empId == -1) return 1;
      ids->push_back(empId);
      return 0;

    }
         }
  }
 