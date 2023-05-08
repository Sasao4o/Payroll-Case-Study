#include "../../Headers/Database/SaveEmployeeOperation.h"

//THIS SHOWS WE Have OCP Violation as we depends on impelementation
#include "../../Headers/PayClassification/ComissionPayClassification.h"

#include "../../Headers/PayClassification/HourlyPayClassification.h"

#include "../../Headers/PayClassification/MonthlyPayClassification.h"

#include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"

#include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"


#include "../../Headers/PayMethod/DirectPayMethod.h"

#include "../../Headers/PayMethod/HoldPayMethod.h"

#include "../../Headers/PayMethod/MailPayMethod.h"

#include "../../Headers/Affiliation/Affiliation.h"

// END

#include "./sqlite3.h"

namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
    SaveEmployeeOperation::SaveEmployeeOperation(int id, Employee * emp, sqlite3 * dbConnection) {
      this -> id = id;
      this -> emp = emp;
      this -> DatabaseConnection = dbConnection;

    }
    void SaveEmployeeOperation::SaveEmployeeOperation::Execute() {

      int rc;
      char * zErrMsg = 0;
      PreSavePaymentMethod(emp);
      PreSaveClassificationType(emp);
      rc = sqlite3_exec(DatabaseConnection, "BEGIN TRANSACTION;", NULL, NULL, & zErrMsg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: Transaction Failed %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Executing Transaction.....\n");
      }

      CreateEmployee();
 
      if (insertPaymentMethodQuery.size() != 0) {

        rc = sqlite3_exec(DatabaseConnection, insertPaymentMethodQuery.c_str(), 0, 0, & zErrMsg);

        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      }
      if (insertClassificationQuery.size() != 0) {

        rc = sqlite3_exec(DatabaseConnection, insertClassificationQuery.c_str(), 0, 0, & zErrMsg);

        if (rc != SQLITE_OK) {
          sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          fprintf(stdout, "Query Executed\n");
        }
      }

      sqlite3_exec(DatabaseConnection, "END TRANSACTION;", NULL, NULL, NULL);
    }

    std::string SaveEmployeeOperation::
    getScheduleKey(PayrollCaseStudy::SchedulesBag::PaymentSchedule * paySchedule) {
      //This depends on the implementation and violates OCP heavilyyy
      if (dynamic_cast < PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule * > (paySchedule) != nullptr) {
        return "weekly";

      }
      if (dynamic_cast < PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule * > (paySchedule) != nullptr) {
        return "monthly";
      }

      return "unknwon";
    }

    std::string SaveEmployeeOperation::quotesql(const std::string & s) {
      return std::string("'") + s + std::string("'");
    }

    void SaveEmployeeOperation::CreateEmployee() {
      int age = emp -> age;
      std::string name = emp -> name;
      std::string email = emp -> email;
      std::string address = emp -> address;
      std::string scheduleType = getScheduleKey(emp -> paySchedule);
      std::string sql;
      char * zErrMsg = 0;
      int rc;
      sql = "INSERT INTO Employee (EmpId,Name,Email,Age,Address, ScheduleType,PaymentMethodType,PaymentClassificationType) "\
      "VALUES (" + std::to_string(id) + "," + quotesql(name) + "," + quotesql(email) + "," + std::to_string(age) + +"," + quotesql(address) +
        "," + quotesql(scheduleType) + "," + quotesql(methodCode) + "," + quotesql(classificationCode) + ");";
      const char * sqlQuery = sql.c_str();
      rc = sqlite3_exec(DatabaseConnection, sqlQuery, 0, 0, & zErrMsg);
      if (rc != SQLITE_OK) {
        sqlite3_exec(DatabaseConnection, "ROLLBACK;", NULL, NULL, NULL);
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        fprintf(stdout, "Query Executed\n");
      }
    }

    void SaveEmployeeOperation::PreSavePaymentMethod(Employee * emp) {
      //This depends on the implementation and violates OCP heavilyyy
      //this method violates single responsiplity as it put in the methodCode to be inserted in employee table
      //and also insert in payment related table but it has very good attuide as it is concentrated not spreaded!
      std::string sql;

      char * zErrMsg = 0;
      if (dynamic_cast < PayrollCaseStudy::MethodsBag::DirectPayMethod * > (emp -> payMethod) != nullptr) {
        methodCode = "direct";
        std::string bankAccount = ((PayrollCaseStudy::MethodsBag::DirectPayMethod * )(emp -> payMethod)) -> bankAccount;
        std::string account = ((PayrollCaseStudy::MethodsBag::DirectPayMethod * )(emp -> payMethod)) -> account;
        int id = emp -> id;

        sql = "INSERT INTO DirectDepositAccount (EmpId,Account,Bank) "\
        "VALUES (" + std::to_string(id) + "," + quotesql(account) + "," + quotesql(bankAccount) + " );";
        //  const char *sqlQuery = sql.c_str();
        insertPaymentMethodQuery = sql;
      }
      else if (dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (emp -> payMethod) != nullptr) {
        methodCode = "mail";
        std::string mailAddress = ((PayrollCaseStudy::MethodsBag::MailPayMethod * )(emp -> payMethod)) -> mailAdress;
        int id = emp -> id;

        sql = "INSERT INTO PayCheckAddress (EmpId,Address) "\
        "VALUES (" + std::to_string(id) + "," + quotesql(mailAddress) + " );";
        //  const char *sqlQuery = sql.c_str();
        insertPaymentMethodQuery = sql;
      }
      else if (dynamic_cast < PayrollCaseStudy::MethodsBag::HoldPayMethod * > (emp -> payMethod) != nullptr) {
        methodCode = "hold";
      }

    }

    void SaveEmployeeOperation::PreSaveClassificationType(Employee * emp) {
      //This depends on the implementation and violates OCP heavilyyy
      //this method violates single responsiplity as it put in the methodCode to be inserted in employee table
      //and also insert in payment related table but it has very good attuide as it is concentrated not spreaded!
      std::string sql;

      char * zErrMsg = 0;
      if (dynamic_cast < PayrollCaseStudy::Classification::ComissionPayClassification * > (emp -> pay) != nullptr) {
        classificationCode = "commission";

        int id = emp -> id;
        float baseRate = ((PayrollCaseStudy::Classification::ComissionPayClassification * )(emp -> pay)) -> baseRate;
        float commissionRate = ((PayrollCaseStudy::Classification::ComissionPayClassification * )(emp -> pay)) -> comissionRate;
        sql = "INSERT INTO CommissionClassification (EmpId,Salary,Commission) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(baseRate) + "," + std::to_string(commissionRate) + " );";
        //  const char *sqlQuery = sql.c_str();
        insertClassificationQuery = sql;
      }
      if (dynamic_cast < PayrollCaseStudy::Classification::HourlyPayClassification * > (emp -> pay) != nullptr) {
        classificationCode = "hourly";
        float hourRate = ((PayrollCaseStudy::Classification::HourlyPayClassification * )(emp -> pay)) -> hourRate;
        int id = emp -> id;

        sql = "INSERT INTO HourlyClassification (EmpId,HourlyRate) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(hourRate) + " );";
        //  const char *sqlQuery = sql.c_str();
        insertClassificationQuery = sql;
      }
      if (dynamic_cast < PayrollCaseStudy::Classification::MonthlyPayClassification * > (emp -> pay) != nullptr) {
        classificationCode = "monthly";
        int salary = ((PayrollCaseStudy::Classification::MonthlyPayClassification * )(emp -> pay)) -> monthlyPay;
        int id = emp -> id;

        sql = "INSERT INTO SalaryClassification (EmpId,Salary) "\
        "VALUES (" + std::to_string(id) + "," + std::to_string(salary) + " );";
        //  const char *sqlQuery = sql.c_str();
        insertClassificationQuery = sql;
      }

    }
 
 
  }

}