#include "./sqlite3.h"

#include<string>

#include<vector>

#include<assert.h>

#include "../Headers/Database/PayrollDatabase.h"

#include "../Headers/Database/SqlDb.h"

#include "../Headers/Database/Employee.h"

#include "../Headers/Transaction/AddHourlyEmployeeTransaction.h"

#include "../Headers/Transaction/AddSalariedEmployeeTransaction.h"

#include "../Headers/Transaction/AddEmployeeTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeEmailTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeNameTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeDirectMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeMailMethodTransaction.h"

#include "../Headers/PayMethod/DirectPayMethod.h"

#include "../Headers/PayMethod/HoldPayMethod.h"

#include "../Headers/PayMethod/MailPayMethod.h"

#include "../Headers/Transaction/ChangeEmployeeHoldMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeUnionTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeNoUnionTransaction.h"

#include "../Headers/PayClassification/MonthlyPayClassification.h"

#include "../Headers/PaySchedule/WeeklyPaymentSchedule.h"
#include "../Headers/PaySchedule/MonthlyPaymentSchedule.h"
#include "../Headers/Affiliation/NoAffiliation.h"

#include "../Headers/Affiliation/UnionAffiliation.h"

#include "../Headers/Affiliation/Affiliation.h"

#include "../Headers/PayClassification/HourlyPayClassification.h"
#include "../Headers/PayClassification/ComissionPayClassification.h"
using namespace PayrollCaseStudy::PayrollEMPDB;
using namespace PayrollCaseStudy::TransactionBag;
using namespace PayrollCaseStudy::MethodsBag;
using namespace PayrollCaseStudy::AffiliationBag;
using namespace PayrollCaseStudy::Classification;
using namespace PayrollCaseStudy::SchedulesBag;
class SqlDbTest {
  public: 
  sqlite3 * Database;
  SqlDb * sqlDb;
  char * zErrMsg = 0;
  void SetUp() {
    int rc;
    rc = sqlite3_open("payrollDb.db", & Database);
    std::string enableForeignKey = "PRAGMA foreign_keys = ON;";

    sqlDb = new SqlDb();

    rc = sqlite3_exec(Database, enableForeignKey.c_str(), 0, 0, & zErrMsg);

    CleanTables();
    if (rc) {
      fprintf(stderr, "Can't open database: With Foreign Key Constraints%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, "Opened database successfully\n");
    }

    char * zErrMsg = 0;

    //Open PayrollDB and create if it doesn't exists

    if (rc) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(Database));
      return;
    } else {
      fprintf(stderr, "Opened database successfully\n");
    }
  }
  void TearUp() {
    sqlite3_close(Database);
  }
  void CleanTables() {
    assert(Database != 0);
    if (Database == 0) return;
    int rc;
    std::string sql;
    char * zErrMsg = 0;
    sql = "DELETE FROM DirectDepositAccount";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
   sql = "DELETE FROM PayCheckAddress";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM EmployeeMemberShip";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM EmployeeAffiliation";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted from EmployeeAff successfully\n");
    }
    sql = "DELETE  FROM ServiceCharge";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
    sql = "DELETE  FROM Affiliation";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error in Affiliation%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }

    sql = "DELETE  FROM SalaryClassification";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted successfully\n");
    }
    sql = "DELETE FROM HourlyClassification";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM CommissionClassification";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM TimeCard";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }
    sql = "DELETE FROM SaleReceipt";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }

    sql = "DELETE FROM Employee";
    rc = sqlite3_exec(Database, sql.c_str(), 0, 0, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Deleted From Employee Done successfully\n");
    }

  }

  void TestAddEmployee() {
    int empId = 1;
    PayClassification * payClass = new MonthlyPayClassification(31);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    sqlDb -> AddEmployee(empId, e);

    int rc;
    std::string sql;
    char * zErrMsg = 0;
    int count;
    /*
    We Will Test By Checking That all the affected tables has count = 1
    */

    sql = "SELECT COUNT(*) FROM Employee";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }

    sql = "SELECT COUNT(*) FROM DirectDepositAccount";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }
    assert(count == 1);

    sql = "SELECT COUNT(*) FROM SalaryClassification";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }
    assert(count == 1);
  }

  void TestAddEmployeeAtomicty() {
    //This Test the Atomicity of The 3 Tables Insertions
    int empId = 1;
    PayClassification * payClass = new MonthlyPayClassification(31);
    PayMethod * payMethod = new DirectPayMethod("", "");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    sqlDb -> AddEmployee(empId, e);

    int rc;
    std::string sql;
    char * zErrMsg = 0;
    int count;
    /*
    We Will Test By Checking That all the affected tables has count = 1
    This Tests Depend On Thec Check Constraints Of DirectDepositTable as it doesn't accept
    empty strings
    */

    sql = "SELECT COUNT(*) FROM Employee";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }

    sql = "SELECT COUNT(*) FROM DirectDepositAccount";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }
    assert(count == 0);

    sql = "SELECT COUNT(*) FROM SalaryClassification";
    count = 0;
    rc = sqlite3_exec(Database, sql.c_str(), countCallBack, & count, & zErrMsg);
    if (rc) {
      fprintf(stderr, "Error%s\n", sqlite3_errmsg(Database));

    } else {
      fprintf(stderr, " Query Executed successfully\n");
    }
    assert(count == 0);
  }
  void TestGetEmployee() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    PayClassification * payClass = new MonthlyPayClassification(monthlyPay);
    PayMethod * payMethod = new MailPayMethod("dummyadd");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    Employee * returnedEmp = sqlDb -> getEmployee(empId);
    assert(returnedEmp != 0);
    assert(returnedEmp->email == "sasax2001@gmail.com");
    assert(returnedEmp -> id == empId);
    assert(returnedEmp -> pay != 0);
    assert(((MonthlyPayClassification * )(returnedEmp -> pay)) -> monthlyPay == monthlyPay);
    assert(returnedEmp -> payMethod != 0);
    // assert(((DirectPayMethod * )(returnedEmp -> payMethod)) -> bankAccount == "dummy");
    assert(returnedEmp -> paySchedule != 0);
    assert(dynamic_cast < PayrollCaseStudy::SchedulesBag::WeeklyPaymentSchedule * > (paySchedule) != nullptr);
  }
  void TestAddAffiliation() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    PayClassification * payClass = new MonthlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    Affiliation * aff = new UnionAffiliation(memberId, weeklyDues);
    e -> setUnionAff(aff);
    sqlDb -> AddUnionMember(memberId, e);

  }

  void TestAddServiceCharge() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int charge = 10;
    PayClassification * payClass = new MonthlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    Affiliation * aff = new UnionAffiliation(memberId, weeklyDues);
    e -> setUnionAff(aff);
    sqlDb -> AddUnionMember(memberId, e);
    sqlDb -> AddSerivceCharge(e, std::time(0), charge);
    sqlDb -> AddSerivceCharge(e, std::time(0) + 2221000, charge + 10);
    //Test Results From Database

    Employee * returnedEmp = sqlDb -> getEmployee(empId);
    assert(returnedEmp -> unionAff -> getDues() == weeklyDues);
    int numbersOfServiceCharge = ((UnionAffiliation * ) returnedEmp -> unionAff) -> serviceCharge.size();
 
    assert(numbersOfServiceCharge == 2);
    std::map < time_t, int > ::iterator it;
    for (it = ((UnionAffiliation * ) returnedEmp -> unionAff) -> serviceCharge.begin(); it != ((UnionAffiliation * ) returnedEmp -> unionAff) -> serviceCharge.end(); it++) {
      assert(it -> second == charge || it -> second == charge + 10);
    }

  }
  void TestAddTimeCard() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area

    sqlDb -> AddTimeCard(e, std::time(0), hours);

    //Test Results From Database

    Employee * returnedEmp = sqlDb -> getEmployee(empId);
    assert(((HourlyPayClassification * ) returnedEmp -> pay) != 0);
    assert(((HourlyPayClassification * ) returnedEmp -> pay) -> timeCards.size() == 2);

    std::map < time_t, int > ::iterator it;
    for (it = ((UnionAffiliation * ) returnedEmp -> unionAff) -> serviceCharge.begin(); it != ((UnionAffiliation * ) returnedEmp -> unionAff) -> serviceCharge.end(); it++) {
      assert(it -> second == hours);
    }

  }
   void TestAddSaleReceipt() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    float amount = 10;
    PayClassification * payClass = new ComissionPayClassification(500, 500);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area

    sqlDb -> AddSaleReceipt(e, std::time(0), amount);
    sqlDb -> AddSaleReceipt(e, std::time(0), amount);
    //Test Results From Database

    Employee * returnedEmp = sqlDb -> getEmployee(empId);
    assert(((ComissionPayClassification * ) returnedEmp -> pay) != 0);
    
    assert(((ComissionPayClassification * ) returnedEmp -> pay) -> salesReceipt.size() == 2);
 

  }
  
  void TestAddMailMethodEmployee() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new MailPayMethod("dummyAddress");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area

  Employee * returnedEmp = sqlDb -> getEmployee(empId);
//  assert(dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (returnedEmp->payMethod) != nullptr);


  }


    void TestDeleteEmployee() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new MailPayMethod("dummyAddress");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area

    sqlDb -> DeleteEmployee(empId);
    Employee * returnedEmp = sqlDb -> getEmployee(empId);
     assert(returnedEmp == 0);
 
    // assert(returnedEmp == 0);
//  assert(dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (returnedEmp->payMethod) != nullptr);


  }

     void TestUpdateEmployeeName() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new MailPayMethod("dummyAddress");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area

    sqlDb -> UpdateEmployee(empId, "Name", "hashem");
 
 
    // assert(returnedEmp == 0);
//  assert(dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (returnedEmp->payMethod) != nullptr);


  }


  void TestUpdateEmployeePayMethod() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummyAddress", "dummyAcc");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    PayMethod *newPayMethod = new DirectPayMethod("dummy2", "dummy2");
    sqlDb -> UpdateEmpPayMethod(e->id, newPayMethod);
 
 
    // assert(returnedEmp == 0);
//  assert(dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (returnedEmp->payMethod) != nullptr);


  }

    void TestUpdateEmployeeSchedule() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    int hours = 10;
    PayClassification * payClass = new HourlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummyAddress", "dummyAcc");
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    PaymentSchedule *newPaySchedule = new MonthlyPaymentSchedule();
    sqlDb -> UpdateEmpPaySchedule(e->id, newPaySchedule);
 
 
    // assert(returnedEmp == 0);
//  assert(dynamic_cast < PayrollCaseStudy::MethodsBag::MailPayMethod * > (returnedEmp->payMethod) != nullptr);


  }
  
  void TestGetEmpIdForMember() {
    //We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    PayClassification * payClass = new MonthlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    Affiliation * aff = new UnionAffiliation(memberId, weeklyDues);
    e -> setUnionAff(aff);
    sqlDb -> AddUnionMember(memberId, e);

   int returnedEmpId = (PayrollDatabase::instance)->getUnionMember(memberId);
 
   assert(returnedEmpId == empId);

  }

  void TestDeleteAffiliation() {

//We will add Employee First
    int empId = 1;
    int monthlyPay = 31;
    int memberId = 2;
    int weeklyDues = 10;
    PayClassification * payClass = new MonthlyPayClassification(monthlyPay);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    e -> setPaySchedule(paySchedule);
    sqlDb -> AddEmployee(empId, e);
    //Test Area
    Affiliation * aff = new UnionAffiliation(memberId, weeklyDues);
    e -> setUnionAff(aff);
    sqlDb -> AddUnionMember(memberId, e);

  (PayrollDatabase::instance)->DeleteUnionMember(memberId);
 
   
  }
void TestGetEmployees() {
    int empId = 1;
    PayClassification * payClass = new MonthlyPayClassification(31);
    PayMethod * payMethod = new DirectPayMethod("dummy", "dummy");;
    WeeklyPaymentSchedule * paySchedule = new WeeklyPaymentSchedule();
    Employee * e = new Employee(empId, "Mostafa", "sasax2001@gmail.com", 41, "saleh ali", payClass, payMethod);
    sqlDb -> AddEmployee(empId, e);

    int rc;
    std::string sql;
    char * zErrMsg = 0;
    std::vector<int> empIds = sqlDb->getEmployees();
      for (int i = 0; i < empIds.size(); i++) {
        std::cout << empIds[i] << std::endl;
      }
    assert(empIds.size() == 1);
}
  static int countCallBack(void * count, int argc, char ** argv, char ** azColName) {
    int * c = (int * ) count;
    * c = atoi(argv[0]);
    return 0;
  }

};