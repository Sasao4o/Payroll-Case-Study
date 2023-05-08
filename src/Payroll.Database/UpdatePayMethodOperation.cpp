
#include "../../Headers/Database/UpdatePayMethodOperation.h"
#include "../../Headers/PayMethod/DirectPayMethod.h"
#include "../../Headers/PayMethod/MailPayMethod.h"
#include "../../Headers/PayMethod/HoldPayMethod.h"
#include "../../Headers/Database/Employee.h"
using PayrollCaseStudy::PayrollEMPDB::Employee;
using PayrollCaseStudy::MethodsBag::PayMethod;
namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
    UpdatePayMethodOperation::UpdatePayMethodOperation(Employee *emp, PayMethod*payMethod, sqlite3*db) {
        this->emp = emp;
        this->payMethod = payMethod;
        this->DatabaseConnection = db;
    }



void UpdatePayMethodOperation::Execute() {
  // std::cout << "Student id 7:33 " << emp->id << std::endl; 
    int rc;
    char *zErrMsg;
    rc = sqlite3_exec(DatabaseConnection, "BEGIN TRANSACTION;", NULL, NULL, & zErrMsg);
    DeleteOldMethod();
    AddNewMethod();
      sqlite3_exec(DatabaseConnection, "END TRANSACTION;", NULL, NULL, NULL);
    }
      void UpdatePayMethodOperation::AddNewMethod() {
       std::string methodCode = insertPayMethod(payMethod);
       std::string sql;
            char * zErrMsg = 0;
      int rc;
      sql = "UPDATE Employee SET PaymentMethodType =" + quotesql(methodCode) + "WHERE EmpId = " +  std::to_string(this->emp->id) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
 
         if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Update Employee PayMethod Query Executed\n");
        }
    }

    void UpdatePayMethodOperation::DeleteOldMethod() {
    char * zErrMsg = 0;
      int rc;
      std::string sql;
      std::string methodType;
      sql = "SELECT * FROM Employee WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectEmployeeData, & methodType, & zErrMsg);

      if (methodType == "direct") {
      sql = "DELETE  FROM DirectDepositAccount WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
      
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Delete From DirectDeposit Query Executed\n");
        }
      } else if (methodType == "mail") {
      sql = "DELETE  FROM PayCheckAddress WHERE EmpId =" + std::to_string(this->emp->id) + ";";
       
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
      
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Delete From PayCheck Query Executed\n");
        }
      }
    }

     
int UpdatePayMethodOperation::injectEmployeeData(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      std::string * patMethod = static_cast < std::string * > (data);
   
      std::string PaymentMethodType;
    
      for (int i = 0; i < numberOfColumns; i++) {
        if (!strcmp(columnNames[i], "PaymentMethodType")) {
          PaymentMethodType = rowData[i];
            break;
        }  

      }
        *patMethod = PaymentMethodType;
      return 0;
    }

std::string UpdatePayMethodOperation::insertPayMethod(PayMethod*payMethod) {
  std::string methodCode;
  std::string sql;
  int rc;
  char * zErrMsg = 0;
  if (dynamic_cast < PayrollCaseStudy::MethodsBag::DirectPayMethod * > (payMethod) != nullptr) {
        methodCode = "direct";
        std::string bankAccount = ((PayrollCaseStudy::MethodsBag::DirectPayMethod * )( payMethod)) -> bankAccount;
        std::string account = ((PayrollCaseStudy::MethodsBag::DirectPayMethod * )(payMethod)) -> account;
        int id = emp -> id;

        sql = "INSERT INTO DirectDepositAccount (EmpId,Account,Bank) "\
        "VALUES (" + std::to_string(id) + "," + quotesql(account) + "," + quotesql(bankAccount) + " );";
        
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);

        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "INSERT NEW PAYMETHOD Query Executed\n");
        }
      }
      else if (dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (payMethod) != nullptr) {
        methodCode = "mail";
        std::string mailAddress = ((PayrollCaseStudy::MethodsBag::MailPayMethod * )( payMethod)) -> mailAdress;
        int id = emp -> id;

        sql = "INSERT INTO PayCheckAddress (EmpId,Address) "\
        "VALUES (" + std::to_string(id) + "," + quotesql(mailAddress) + " );";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), 0, 0, & zErrMsg);
        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Insert into Paycheck Query Executed\n");
        }
      }
      else if (dynamic_cast < PayrollCaseStudy::MethodsBag::HoldPayMethod * > (payMethod) != nullptr) {
        methodCode = "hold";
      }
      
      return methodCode;
}

  std::string UpdatePayMethodOperation::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }
  }
}