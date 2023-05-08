
#include "../../Headers/Database/UpdatePayClassificationOperation.h"
#include"../../Headers/PayClassification/ComissionPayClassification.h"
#include"../../Headers/PayClassification/HourlyPayClassification.h"
#include"../../Headers/PayClassification/MonthlyPayClassification.h"
#include "../../Headers/Database/Employee.h"
using PayrollCaseStudy::PayrollEMPDB::Employee;
using PayrollCaseStudy::MethodsBag::PayMethod;
namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
    UpdatePayClassificationOperation::UpdatePayClassificationOperation(Employee *emp, PayrollCaseStudy::Classification::PayClassification*payClass, sqlite3*db) {
        this->emp = emp;
        this->payClass = payClass;
        this->DatabaseConnection = db;
    }



void UpdatePayClassificationOperation::Execute() {
    int rc;
    char *zErrMsg;
    rc = sqlite3_exec(DatabaseConnection, "BEGIN TRANSACTION;", NULL, NULL, & zErrMsg);
    DeleteOldClassification();
    AddNewClassification();
      sqlite3_exec(DatabaseConnection, "END TRANSACTION;", NULL, NULL, NULL);
    }
      void UpdatePayClassificationOperation::AddNewClassification() {
       std::string methodCode = insertPayClass(payClass);
       std::string sql;
            char * zErrMsg = 0;
      int rc;
      std::cout << " i will be fine " << methodCode;
      sql = "UPDATE Employee SET PaymentClassificationType =" + quotesql(methodCode) + "WHERE EmpId = " +  std::to_string(this->emp->id) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
 
         if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Update Employee PaymentClassificationType Query Executed\n");
        }
    }

    void UpdatePayClassificationOperation::DeleteOldClassification() {
    char * zErrMsg = 0;
      int rc;
      std::string sql;
      std::string classificationType;
      sql = "SELECT * FROM Employee WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectEmployeeData, & classificationType, & zErrMsg);

      if (classificationType == "comission") {
      sql = "DELETE  FROM CommissionClassification WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
      
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      } else if (classificationType == "hourly") {
      sql = "DELETE  FROM HourlyClassification WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
      
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      }
       else if (classificationType == "monthly") {
      sql = "DELETE  FROM SalaryClassification WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
      
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      }
    }

     
int UpdatePayClassificationOperation::injectEmployeeData(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      std::string * payClassN = static_cast < std::string * > (data);
   
      std::string PaymentClassificationType;
    
      for (int i = 0; i < numberOfColumns; i++) {
        if (!strcmp(columnNames[i], "PaymentClassificationType")) {
          PaymentClassificationType = rowData[i];
            break;
        }  

      }
        *payClassN = PaymentClassificationType;
      return 0;
    }

std::string UpdatePayClassificationOperation::insertPayClass(PayClassification*payClass) {
  std::string classificationCode;
  std::string sql;
  int rc;
  char * zErrMsg = 0;
    if (dynamic_cast < PayrollCaseStudy::Classification::ComissionPayClassification * > (payClass) != nullptr) {
        classificationCode = "commission";

        int id = emp -> id;
        float baseRate = ((PayrollCaseStudy::Classification::ComissionPayClassification * )(payClass)) -> baseRate;
        float commissionRate = ((PayrollCaseStudy::Classification::ComissionPayClassification * )(payClass)) -> comissionRate;
        sql = "INSERT INTO CommissionClassification (EmpId,Salary,Commission) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(baseRate) + "," + std::to_string(commissionRate) + " );";
        //  const char *sqlQuery = sql.c_str();
 
      }
      if (dynamic_cast < PayrollCaseStudy::Classification::HourlyPayClassification * > (payClass) != nullptr) {
        classificationCode = "hourly";
        float hourRate = ((PayrollCaseStudy::Classification::HourlyPayClassification * )(payClass)) -> hourRate;
        int id = emp -> id;

        sql = "INSERT INTO HourlyClassification (EmpId,HourlyRate) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(hourRate) + " );";
        //  const char *sqlQuery = sql.c_str();
 
      }
      if (dynamic_cast < PayrollCaseStudy::Classification::MonthlyPayClassification * > (payClass) != nullptr) {
        classificationCode = "monthly";
        int salary = ((PayrollCaseStudy::Classification::MonthlyPayClassification * )(payClass)) -> monthlyPay;
        int id = emp -> id;

        sql = "INSERT INTO SalaryClassification (EmpId,Salary) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(salary) + " );";
        //  const char *sqlQuery = sql.c_str();
        
      }

        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      return classificationCode;
}

  std::string UpdatePayClassificationOperation::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }
  }
}