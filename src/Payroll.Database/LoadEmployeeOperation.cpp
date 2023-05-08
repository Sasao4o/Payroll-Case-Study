#include "../../Headers/Database/LoadEmployeeOperation.h"

#include "../../Headers/Affiliation/Affiliation.h"
 //THIS SHOWS WE Have OCP Violation as we depends on impelementation
#include "../../Headers/PayClassification/ComissionPayClassification.h"

#include "../../Headers/PayClassification/HourlyPayClassification.h"

#include "../../Headers/PayClassification/MonthlyPayClassification.h"

#include "../../Headers/PayMethod/DirectPayMethod.h"

#include "../../Headers/PayMethod/MailPayMethod.h"
#include "../../Headers/PayMethod/HoldPayMethod.h"
#include "../../Headers/PaySchedule/WeeklyPaymentSchedule.h"

#include "../../Headers/PaySchedule/MonthlyPaymentSchedule.h"


#include "../../Headers/Affiliation/UnionAffiliation.h"


namespace PayrollCaseStudy {
  namespace PayrollEMPDB {
    using namespace PayrollCaseStudy::Classification;
    using namespace PayrollCaseStudy::SchedulesBag;
    using namespace PayrollCaseStudy::MethodsBag;
    using namespace PayrollCaseStudy::AffiliationBag;
    LoadEmployeeOperation::LoadEmployeeOperation(int id, sqlite3 * dbConnection) {
      this -> id = id;
      this -> DatabaseConnection = dbConnection;

    }
    void LoadEmployeeOperation::Execute() {
      //note this operator may lead to unexpected behaviour as it creats the object using default constructor if it doesn;t find it

      char * zErrMsg = 0;
      int rc;
      //Open PayrollDB and create if it doesn't exists

      std::string sql;

      sql = "SELECT * FROM Employee WHERE EmpId =" + std::to_string(id) + ";";
      struct EmployeeRecord empRecord;

      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectEmployeeData, & empRecord, & zErrMsg);
   
      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
        // fprintf(stdout, "SELECTION FROM EMPLOYEE Query Executed\n");
      }
    
      if (empRecord.empId == -1) {
        emp = 0;
        return;
      };
      PaymentSchedule * paySchedule = LoadEmployeeSchedule(empRecord.ScheduleType);
      PayClassification * payClass = LoadEmployeeClassification(empRecord.PaymentClassificationType);
      PayMethod * payMethod = LoadEmployeeMethod(empRecord.PaymentMethodType);

      emp = new Employee(id, empRecord.name, empRecord.email, empRecord.age, empRecord.address, payClass, payMethod);
      if (paySchedule != 0) {
        emp -> setPaySchedule(paySchedule);
      }
 
       LoadEmployeeClassificationData(empRecord.PaymentClassificationType, payClass);
      int affId = LoadAffiliationId(id);
      if (affId == -1) return;
      int memberId = LoadMemberId(id);
      if (memberId == -1) return;
      Affiliation * aff = LoadAffiliation(memberId, affId);
      emp -> setUnionAff(aff);
      LoadServiceCharge(affId, aff);
           
      
    }
    int LoadEmployeeOperation::injectEmployeeData(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      EmployeeRecord * employeeRecord = static_cast < EmployeeRecord * > (data);
      int i;
      int empId = -1;
      std::string name;
      std::string email;
      int age;
      std::string address;
      std::string ScheduleType;
      std::string PaymentMethodType;
      std::string PaymentClassificationType;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "EmpId")) {
          empId = atoi(rowData[i]);

        } else if (!strcmp(columnNames[i], "Name")) {

          name = rowData[i];
        } else if (!strcmp(columnNames[i], "Email")) {
          
          email = rowData[i];
 
        } else if (!strcmp(columnNames[i], "Age")) {
          age = atoi(rowData[i]);

        } else if (!strcmp(columnNames[i], "Address")) {
          address = rowData[i];

        } else if (!strcmp(columnNames[i], "ScheduleType")) {

          // fetchScheduleType(rowData[i], empId)
          ScheduleType = rowData[i];

        } else if (!strcmp(columnNames[i], "PaymentMethodType")) {
          PaymentMethodType = rowData[i];

        } else if (!strcmp(columnNames[i], "PaymentClassificationType")) {

          PaymentClassificationType = rowData[i];
        } else {
          // std::cout << "ERRRRORRRRR from employee creation";
        }

      }
      employeeRecord -> empId = empId;
      employeeRecord -> name = name;
      employeeRecord -> email = email;
      employeeRecord -> age = age;
      employeeRecord -> address = address;
      employeeRecord -> ScheduleType = ScheduleType;
      employeeRecord -> PaymentMethodType = PaymentMethodType;
      employeeRecord -> PaymentClassificationType = PaymentClassificationType;

      return 0;
    }

    int LoadEmployeeOperation::injectComissionPayClass(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      ComissionPayClassification ** comissionPayClass = static_cast < ComissionPayClassification ** > (data);
      float salary = 0;
      float commission = 0;
      int i;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "Salary")) {
          salary = std::stof(rowData[i]);

        } else if (!strcmp(columnNames[i], "Commission")) {
          commission = std::stof(rowData[i]);
        } else {
          // std::cout << "ERRRRORRRRR from ComissionPayClassification creation";
        }
        * comissionPayClass = new ComissionPayClassification(salary, commission);
      }

      return 0;
    }

    int LoadEmployeeOperation::injectHourlyPayClass(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      HourlyPayClassification ** hourlyPayClass = static_cast < HourlyPayClassification ** > (data);
      float hourRate = 0;

      int i;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "HourlyRate")) {
          hourRate = std::stof(rowData[i]);

        } else {
          // std::cout << "ERRRRORRRRR";
        }
        * hourlyPayClass = new HourlyPayClassification(hourRate);
      }

      return 0;
    }

    int LoadEmployeeOperation::injectMonthlyPayClass(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      // std::cout << "FromXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Injectionm Process";
      MonthlyPayClassification ** monthlyPayClass = static_cast < MonthlyPayClassification ** > (data);
      float salary = 0;

      int i;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "Salary")) {
          salary = atoi(rowData[i]);

        } else {
          // std::cout << "another field";
        }

        * monthlyPayClass = new MonthlyPayClassification(salary);
      }

      return 0;
    }
    int LoadEmployeeOperation::injectDirectPayMethod(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {

      DirectPayMethod ** directMethod = static_cast < DirectPayMethod ** > (data);
      std::string account = "";
      std::string bank = "";
      int i;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "Bank")) {
          bank = rowData[i];

        } else if (!strcmp(columnNames[i], "Account")) {
          account = rowData[i];
        } else {
          // std::cout << "aother field";
        }
        * directMethod = new DirectPayMethod(bank, account);
      }

      return 0;
    }
    int LoadEmployeeOperation::injectMailPayMethod(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      MailPayMethod ** mailMethod = static_cast < MailPayMethod ** > (data);
      std::string address = "";
  
      int i;
      for (i = 0; i < numberOfColumns; i++) {
        // std::cout << std::endl << "Column name is" << columnNames[i] << "Row Data is " << rowData[i] << std::endl;
        if (!strcmp(columnNames[i], "Address")) {
     
          address = rowData[i];

        } else {
          // std::cout << "aother field";
        }
        * mailMethod = new MailPayMethod(address);
      }

      return 0;
    }
    Employee * LoadEmployeeOperation::getEmployee() {
      return emp;
    }

    PaymentSchedule * LoadEmployeeOperation::LoadEmployeeSchedule(std::string type) {
      if (type == "weekly") {
        return new PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule();
      } else if (type == "monthly") {
        return new PayrollCaseStudy::SchedulesBag::MonthlyPaymentSchedule();
      }
    }
    PayClassification * LoadEmployeeOperation::LoadEmployeeClassification(std::string type) {

      std::string sql;
      char * zErrMsg = 0;
      int rc;
      if (type == "commission") {
        ComissionPayClassification * comissionPayClass = 0;
        sql = "SELECT * FROM CommissionClassification WHERE EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectComissionPayClass, & comissionPayClass, & zErrMsg);
        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM CommissionClassification Query Executed\n");
        }

        return comissionPayClass;

      } else if (type == "hourly") {
        HourlyPayClassification * hourlyPayClass = 0;
        sql = "SELECT * FROM  HourlyClassification WHERE  EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectHourlyPayClass, & hourlyPayClass, & zErrMsg);
        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM HourlyClassification Query Executed\n");
        }

        return hourlyPayClass;
      } else if (type == "monthly") {

        MonthlyPayClassification * monthlyPayClass = 0;
        sql = "SELECT * FROM SalaryClassification WHERE  EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectMonthlyPayClass, & monthlyPayClass, & zErrMsg);
        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM MonthlyPayClassification Query Executed\n");
        }

        return monthlyPayClass;
      }
    }
    PayMethod * LoadEmployeeOperation::LoadEmployeeMethod(std::string type) {
      std::string sql;

      char * zErrMsg = 0;
      int rc;
      if (type == "direct") {
  
        DirectPayMethod * directPayMethod = 0;
        sql = "SELECT * FROM  DirectDepositAccount WHERE  EmpId =" + std::to_string(id) + ";";

        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectDirectPayMethod, & directPayMethod, & zErrMsg);

        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM DirectDepositAccount Query Executed\n");
        }

        return directPayMethod;
      } else if (type == "mail") {
        MailPayMethod * mailMethod = 0;
       
        sql = "SELECT * FROM  PayCheckAddress WHERE  EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectMailPayMethod, & mailMethod, & zErrMsg);
        if (rc != SQLITE_OK) {
          // std::cout << "Selection from paycheck ...." << std::endl;
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM PayCheckAddress Query Executed\n");
        }

        return mailMethod;
      } else if (type == "hold") {
        HoldPayMethod *holdMethod = new HoldPayMethod();
        return holdMethod;
      } else {
        return 0;
      }

    }
    int LoadEmployeeOperation::LoadAffiliationId(int empId) {
      std::string sql;
      char * zErrMsg = 0;
      int rc;
      int aff = -1;
      sql = "SELECT * FROM EmployeeAffiliation WHERE EmpId = " + std::to_string(empId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectAffiliationId, & aff, & zErrMsg);
      return aff;
    }
    int LoadEmployeeOperation::LoadMemberId(int empId) {
      std::string sql;
      char * zErrMsg = 0;
      int rc;
      int memberId;
      sql = "SELECT * FROM EmployeeMemberShip WHERE EmpId = " + std::to_string(empId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectMemberId, & memberId, & zErrMsg);
      return memberId;
    }
    Affiliation * LoadEmployeeOperation::LoadAffiliation(int memberId, int affId) {
      std::string sql;
      char * zErrMsg = 0;
      int rc;
      struct AffiliationRecord affRecord;
      sql = "SELECT * FROM Affiliation WHERE AffiliationId = " + std::to_string(affId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectAffiliation, & affRecord, & zErrMsg);
      return new UnionAffiliation(memberId, affRecord.dues);
    }

    void LoadEmployeeOperation::LoadServiceCharge(int affId, Affiliation * aff) {

      std::string sql;
      char * zErrMsg = 0;
      int rc;

      sql = "SELECT  Amount, Date FROM ServiceCharge WHERE AffiliationId = " + std::to_string(affId) + ";";
      rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectServiceCharge, aff, & zErrMsg);

    }
    int LoadEmployeeOperation::injectAffiliationId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      int * aff = static_cast < int * > (data);
      int affiliationId = -1;
      for (int i = 0; i < numberOfColumns; i++) {

        if (!strcmp(columnNames[i], "AffiliationId")) {
          affiliationId = atoi(rowData[i]);

        }
      }
      ( * aff) = affiliationId;
      return 0;
    }
    int LoadEmployeeOperation::injectMemberId(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      int * memberId = static_cast < int * > (data);
      int returnedMemberId = -1;
      for (int i = 0; i < numberOfColumns; i++) {

        if (!strcmp(columnNames[i], "MemberId")) {
          returnedMemberId = atoi(rowData[i]);

        }
      }
      ( * memberId) = returnedMemberId;
      return 0;
    }

    int LoadEmployeeOperation::injectAffiliation(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      AffiliationRecord * aff = static_cast < AffiliationRecord * > (data);
      int dues = -1;
      for (int i = 0; i < numberOfColumns; i++) {

        if (!strcmp(columnNames[i], "Dues")) {
          dues = atoi(rowData[i]);

        }
      }
      if (dues == -1) {
        return 1;
      }
      aff -> dues = dues;
      return 0;
    }

    int LoadEmployeeOperation::injectServiceCharge(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      Affiliation * aff = static_cast < Affiliation * > (data);
      int amount;
      time_t time = -1;

      for (int i = 0; i < numberOfColumns; i++) {
 
        if (!strcmp(columnNames[i], "Amount")) {
          amount = atoi(rowData[i]);

        } else if (!strcmp(columnNames[i], "Date")) {
          time = atoi(rowData[i]);
      
        }
     
      }
    
      ((UnionAffiliation * ) aff) -> addServiceCharge(time, amount);
      return 0;
    }
    void LoadEmployeeOperation::LoadEmployeeClassificationData(std::string type,PayClassification *payClass) {
        std::string sql;
      char * zErrMsg = 0;
      int rc;
      //  std::cout << "HERREEE IS THE TYPEE MAN " << type << std::endl;
      if (type == "commission") {
        
        sql = "SELECT * FROM SaleReceipt WHERE EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectSaleRecipt,  payClass, & zErrMsg);
        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM SaleReceipt Query Executed\n");
        }

 

      } else if (type == "hourly") {
       
        sql = "SELECT * FROM  TimeCard WHERE  EmpId =" + std::to_string(id) + ";";
        rc = sqlite3_exec(DatabaseConnection, sql.c_str(), injectTimeCard, payClass, & zErrMsg);
        if (rc != SQLITE_OK) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        } else {
          // fprintf(stdout, "SELECTION FROM HourlyClassification Query Executed\n");
        }

      
      }  
    }
    int LoadEmployeeOperation::injectSaleRecipt(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      ComissionPayClassification * payClass = static_cast < ComissionPayClassification * > (data);
      float amount;
      time_t time;

      for (int i = 0; i < numberOfColumns; i++) {

        if (!strcmp(columnNames[i], "Amount")) {
          amount = atoi(rowData[i]);

        } else if (!strcmp(columnNames[i], "Date")) {
          time = atoi(rowData[i]);
        }
     
      }
    // std::cout << "Yarb" << amount << std::endl << std::endl;
      payClass->insertSaleTransaction(time, amount);
      return 0;

    }

    int LoadEmployeeOperation::injectTimeCard(void * data, int numberOfColumns, char ** rowData, char ** columnNames) {
      HourlyPayClassification * payClass = static_cast < HourlyPayClassification * > (data);
      int hours;
      time_t time;
  
      for (int i = 0; i < numberOfColumns; i++) {

        if (!strcmp(columnNames[i], "Hours")) {
          hours = atoi(rowData[i]);

        } else if (!strcmp(columnNames[i], "Date")) {
          time = atoi(rowData[i]);
        }
     
      }

      payClass->insertTimeCard(time,hours);
      return 0;

    }
  }

}