#include<iostream>
  #include "../../Headers/Database/PayrollDatabase.h"
 #include "../../Test/PayrollTest.cpp"
 #include "../../Test/SqlDbTest.cpp"
  #include "../../Headers/Database/PayrollDatabase.h"
  #include "../../Headers/Database/InMemoryDb.h"
  #include "../../Headers/Database/SqlDb.h"
 
using namespace std;
using namespace PayrollCaseStudy::PayrollEMPDB;
   PayrollDatabase * PayrollDatabase::instance = new SqlDb();
 
int main() {
 
  PayrollTest x;
  x.SetUp();
  //  x.TestAddHourlyEmployee();
  //     x.TestAddHourlyEmployee();
  //  x.TestAddComissionEmployee();
  //  x.TestAddSalariedEmployee();
  //  x.TestDeleteEmployee();
  //   x.TestChangeEmployee();
  //    x.TestAddSaleReceipt();
  //    x.TestAddTimeCard();
  //    x.TestAddServiceCharge();
  //    x.TestAddEmployeeWithAffilication();
  //  x.TestChangeEmployeeAffilicationTransaction();
  // x.TestChangeEmployeeNoAffilicationTransaction();

  // x.TestPayDayTransactionForSalariedEmployee();
  // x.TestPayDayTransactionForHourlyEmployee();
  // x.TestPayDayTransactionForComissionEmployee();
  // x.TestServiecChargesAndWeeklyDuesDeductions();
  x.TestChangeHoldPayMethod();
  // SqlDbTest x;
  // x.SetUp();
  // x.TestGetEmployees();
  // x.TearUp();

  
// x.TestChangeEmployee();
// x.TestAddEmployeeWithAffilication();
// x.TestAddSaleReceipt();
// x.TestAddServiceCharge();
 
}
