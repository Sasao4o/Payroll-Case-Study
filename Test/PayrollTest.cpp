// #include "../src/Payroll.Database/Employee.cpp"
#include "../Headers/Database/PayrollDatabase.h"

#include "../Headers/Database/Employee.h"

#include "../Headers/Transaction/AddHourlyEmployeeTransaction.h"

#include "../Headers/Transaction/AddSalariedEmployeeTransaction.h"

#include "../Headers/Transaction/AddEmployeeTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeEmailTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeNameTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeDirectMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeMailMethodTransaction.h"
#include "../Headers/Transaction/ChangeEmployeePayClassTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeHourlyTransaction.h"
#include "../Headers/Transaction/AddTimeCardTransaction.h"

#include "../Headers/PayMethod/DirectPayMethod.h"

#include "../Headers/PayMethod/HoldPayMethod.h"

#include "../Headers/PayMethod/MailPayMethod.h"

#include "../Headers/Transaction/ChangeEmployeeHoldMethodTransaction.h"

#include "../Headers/Transaction/ChangeEmployeeUnionTransaction.h"
#include "../Headers/Transaction/AddServiceChargeTransaction.h"
#include "../Headers/Transaction/ChangeEmployeeNoUnionTransaction.h"
#include "../Headers/Transaction/AddComissionEmployeeTransaction.h"
#include "../Headers/Transaction/AddSaleReceiptTransaction.h"
#include "../Headers/Affiliation/NoAffiliation.h"

#include "../Headers/Database/InMemoryDb.h"
#include "../Headers/Transaction/PayDayTransaction.h"
#include "../Headers/PayClassification/MonthlyPayClassification.h"
#include "../Headers/PayClassification/HourlyPayClassification.h"
#include "../Headers/PayClassification/ComissionPayClassification.h"
 // #include "../src/Payroll.Transaction/AddTimeCardTransaction.cpp"
// #include "../src/Payroll.Transaction/AddSaleReceiptTransaction.cpp" 
//  #include "../src/Payroll.Transaction/ChangeEmployeeTransaction.cpp"
//   #include "../src/Payroll.Transaction/AddServiceChargeTransaction.cpp"
//     #include "../src/Payroll.Transaction/PayDayTransaction.cpp"
//  #include "../src/Payroll.Affiliation/Affiliation.cpp"
//  #include "../src/Payroll.Transaction/AddEmployeeTransaction.cpp"
//   #include "../src/Payroll.Transaction/AddSalariedEmployeeTransaction.cpp"
//    #include "../src/Payroll.Transaction/AddHourlyEmployeeTransaction.cpp"
// #include "../src/Payroll.Transaction/AddComissionEmployeeTransaction.cpp"
using namespace PayrollCaseStudy::PayrollEMPDB;
using namespace PayrollCaseStudy::TransactionBag;
using namespace PayrollCaseStudy::MethodsBag;
using namespace PayrollCaseStudy::AffiliationBag;
using namespace PayrollCaseStudy::Classification;
using namespace PayrollCaseStudy::SchedulesBag;
 
#include<assert.h>

#include<iostream>

#include <ctime>

class PayrollTest {

  public:
  int currentEmpId = 0;
    void SetUp() {
      ClearTables();
    }
   int generateEmployeeId() {
    return currentEmpId++;
  }
  void TestAddSalariedEmployee() {
        int empId = generateEmployeeId();
    std::string appEmail = "test@gmail.com" + std::to_string(empId); 
    int appSalary = 500;
    AddEmpoloyeeTransaction * trans = new AddSalariedEmployeeTransaction(empId, "Mostafa", appEmail, 30, 500, "salehAli");
    trans -> Execute();

    Employee * z = (PayrollDatabase::instance) -> getEmployee(empId);
    if (z == 0) {
      return;
    }
     MonthlyPayClassification *payClassification = (dynamic_cast<MonthlyPayClassification*>(z->getPaymentClassification()));
    assert(payClassification != 0); 
    int databaseSalary = payClassification->monthlyPay;
    assert(z -> email == appEmail);
    assert(appSalary == databaseSalary);

  }
  void TestAddComissionEmployee() {
        int empId = generateEmployeeId();
         std::string appEmail = "test@gmail.com" + std::to_string(empId); 
    int appBaseRate = 1000;
    float appComissionRate = 100;
    AddEmpoloyeeTransaction * trans = new AddComissionEmployeeTransaction(empId, "Mostafa", appEmail, 30, appBaseRate,appComissionRate, "salehAli");
    trans -> Execute();

    Employee * z = (PayrollDatabase::instance) -> getEmployee(empId);
    if (z == 0) {
      return;
    }
    ComissionPayClassification *payClassification = (dynamic_cast<ComissionPayClassification*>(z->getPaymentClassification()));
    assert(payClassification != 0);
    int databaseBaseRate = payClassification->baseRate;
    float databaseComissionRate = payClassification->comissionRate;
    assert(z -> email == appEmail);
    assert(appBaseRate == databaseBaseRate);
    assert(appComissionRate == databaseComissionRate);
  }
  void TestAddHourlyEmployee() {
     int empId = generateEmployeeId();
     std::string appEmail = "test@gmail.com" + std::to_string(empId); 
    float appHourRate = 40.5;
    AddEmpoloyeeTransaction * trans = new AddHourlyEmployeeTransaction(empId, "Mostafa", appEmail, 30, appHourRate, "salehAli");
    trans -> Execute();

    Employee * z = (PayrollDatabase::instance) -> getEmployee(empId);
    assert(z != 0);
    HourlyPayClassification *payClassification = (dynamic_cast<HourlyPayClassification*>(z->getPaymentClassification()));
    assert(payClassification != 0);
    float databaseHourRate = payClassification->hourRate;
    assert(z -> email == appEmail);
    assert(appHourRate == databaseHourRate);
 
  }
  void TestDeleteEmployee() {
    int empId = generateEmployeeId();
    std::string email = "test@gmail.com" + empId;
    AddHourlyEmployeeTransaction trans(empId, "Mostafa", email, 30, 304, "SALEHALI");
    trans.Execute();

    (PayrollDatabase::instance) -> DeleteEmployee(empId);
    assert(0 == (PayrollDatabase::instance) -> getEmployee(empId));

  }
  void TestChangeEmployee() {
    //This Function Has many responisibilites
    //TEST CHANGENAME,CHANGEEMAIL,CHANGEPAYCLASSIFICATION 
    int empId = generateEmployeeId();
    std::string email = "test@gmail.com" + std::to_string(empId);
    AddEmpoloyeeTransaction * trans = new AddSalariedEmployeeTransaction(empId, "Mostafa",email, 30, 500, "salehAli");
    trans -> Execute();

    std::string newName = "Medhat";
    std::string newEmail = "testChange@gmail.com" + std::to_string(empId);
    int newHourlyRate = 934.49;
    ChangeEmployeeNameTransaction chngName(empId, newName);
    ChangeEmployeeEmailTransaction chngEmail(empId, newEmail);
    ChangeEmployeeHourlyTransaction chngHourly(empId, newHourlyRate);
    chngName.Execute();
    chngEmail.Execute();
    chngHourly.Execute();
    Employee *dbEmployee = (PayrollDatabase::instance) -> getEmployee(empId);
    assert(newName == dbEmployee-> name);
    assert(newEmail == dbEmployee-> email);
    assert(dynamic_cast<HourlyPayClassification *>(dbEmployee->pay) != nullptr);
  }


  //   void TestChangeDirectPayMethod() {
     
  //    int empId = generateEmployeeId();
  //    std::string email = "test@gmail.com" + std::to_string(empId);
  //    AddEmpoloyeeTransaction * trans = new AddSalariedEmployeeTransaction(empId, "Mostafa",email, 30, 500, "salehAli");
  //     trans -> Execute();
  //     //The test depends that the default pay method is HoldPayMethod

  //     ChangeEmployeeDirectMethodTransaction chng(empId, "dummyBankNumer");
  //     chng.Execute();
  //       Employee*z = PayrollDatabase::getEmployee(4);
  //         if (z == 0) {
  //             return;
  //         }

  //     if (dynamic_cast<DirectPayMethod *>(z->payMethod) != nullptr) {
  //   // aPtr is instance of B
  //         std::cout << "Success";
  //     } else {
  //   // aPtr is NOT instance of B
  //       std::cout << "Fail";
  //         }

  // }

  void TestChangeHoldPayMethod() {
    int empId = generateEmployeeId();
    std::string email = "test@gmail.com" + std::to_string(empId);
    AddEmpoloyeeTransaction * trans = new AddSalariedEmployeeTransaction(empId, "Mostafa",email, 30, 500, "salehAli");
    trans -> Execute();
   
    ChangeEmployeeDirectMethodTransaction chng(empId, "dummyBankNumer" + empId, "dummyAccount" + empId);
    chng.Execute();
    ChangeEmployeeHoldMethodTransaction chngTest(empId);
    chngTest.Execute();
    Employee * z = (PayrollDatabase::instance) -> getEmployee(empId);
    assert(z != 0);
    assert(z->payMethod != 0);
    // if (dynamic_cast < HoldPayMethod * > (z -> payMethod) != nullptr) {
    //   // aPtr is instance of B
    //   std::cout << "Success";
    // } else {
    //   // aPtr is NOT instance of B
    //   std::cout << "Fail";
    // }
  assert(dynamic_cast < HoldPayMethod * > (z -> payMethod) != nullptr);
  }

  // void TestChangeMailMethod() {
       

  //      AddEmpoloyeeTransaction* trans= new AddSalariedEmployeeTransaction (4,"Mostafa" ,"test@gmail.com", 30, 500, "salehAli");
  //     trans->Execute();
  //     //The test depends that the default pay method is HoldPayMethod

  //     ChangeEmployeeMailMethodTransaction chng(4, "dummyMailADDRESS");
  //     chng.Execute();

  //       Employee*z = (PayrollDatabase::instance)->getEmployee(4);
  //         if (z == 0) {
  //             return;
  //         }

  //     assert(dynamic_cast<MailPayMethod *>(z->payMethod) != nullptr);
  //     //Test Area
  //     Employee*returnedEmp = (PayrollDatabase::instance)->getEmployee(4);
  //     assert(((MailPayMethod*)returnedEmp->payMethod)->mailAdress == "dummyMailADDRESS");
    
  // }

      void TestAddTimeCard() {
 
        int empId = generateEmployeeId();
        time_t currentTime = time(0);
         int hours = 5;
         AddHourlyEmployeeTransaction addTxn(empId,"Hesham" ,"test@gmail.com" + std::to_string(empId), 30, 500, "salehAli");
          addTxn.Execute();
          AddTimeCardTransaction timeCardTransaction(empId, (time_t)currentTime, hours);
          timeCardTransaction.Execute();
          Employee* dbEmp = (PayrollDatabase::instance)->getEmployee(empId);
          assert(dbEmp != 0);
          HourlyPayClassification *payX = (dynamic_cast<HourlyPayClassification*>(dbEmp->getPaymentClassification()));
          assert(payX != nullptr);
          int estimatedHours = payX->timeCards[currentTime];
          assert(estimatedHours == hours);
    }
    void TestAddSaleReceipt() {
    int empId = generateEmployeeId();
      time_t currentTime = time(0);
       AddComissionEmployeeTransaction employeeTransaction(empId,"Mostafa" ,"test@gmail.com", 30, 500,400, "saleh ali");
           employeeTransaction.Execute();
          AddSaleReceiptTransaction salesReceipttransaction(empId, (time_t)currentTime, 5);
       salesReceipttransaction.Execute();
          Employee * emp = (PayrollDatabase::instance)->getEmployee(empId);
          if (emp == 0) {
            return;
          }
          ComissionPayClassification *payX = (dynamic_cast<ComissionPayClassification*>(emp->getPaymentClassification()));

          if (payX == 0) return;
          float amount = payX->getSaleReceipt(currentTime);
  
             assert(amount != -1);
           assert(payX->salesReceipt.size() == 1);
           assert(amount == 5);
    }
      void TestAddServiceCharge() {
        int empId = generateEmployeeId();
        int memberId = empId; //to be unique if all tests works togther 
        time_t currentTime = time(0);
       
        int weeklyDues = 20;
      AddSalariedEmployeeTransaction trans(empId,"Mostafa" ,"test@gmail.com" + std::to_string(empId),500, 30, "salehAli");
      trans.Execute();
      Affiliation *uf = new UnionAffiliation(memberId, 10);
      Employee *dbEmp = (PayrollDatabase::instance)->getEmployee(empId);
      assert(dbEmp != 0);
      ChangeEmployeeUnionTransaction changeEmpUXN(empId, memberId, 20);
      changeEmpUXN.Execute();
      AddServiceChargeTransaction addServiceTrans(memberId, currentTime, 999);
      addServiceTrans.Execute();
      //Test Area
      Employee *emp = (PayrollDatabase::instance)->getEmployee(empId);
     int theCharge =  ((UnionAffiliation*)(emp->unionAff))->getServiceCharge(currentTime);
    
 
     assert(theCharge == 999);
      }
      void TestAddEmployeeWithAffilication() {
        int empId = generateEmployeeId();
       
        std::string email = "test@gmail.com" + std::to_string(empId);
        int memberId = empId;
        int weeklyDues = 600;
       //Add Employee Hourly Classification with  unionAffilication
      AddSalariedEmployeeTransaction trans(empId,"Mostafa",email ,30,500, "saleh Ali");
      trans.Execute();
      ChangeEmployeeUnionTransaction chngEmpUnion(empId, memberId, weeklyDues);
      chngEmpUnion.Execute();
      //Test Area
        int returnedEmpId = (PayrollDatabase::instance)->getUnionMember(memberId);
        Employee* dbEmp = (PayrollDatabase::instance)->getEmployee(empId);
        assert(returnedEmpId == empId);
        assert(dbEmp->unionAff->getDues() == weeklyDues);
      }
    void TestChangeEmployeeAffilicationTransaction() {
    int empId = generateEmployeeId();
       
        std::string email = "test@gmail.com" + std::to_string(empId);
        int memberId = empId;
        int newMemberId = (memberId +1) * 1000; //not scalable
        int newWeeklyDues = 40;
        int weeklyDues = 600;
       //Add Employee Hourly Classification with  unionAffilication
       AddSalariedEmployeeTransaction trans(empId,"Mostafa",email ,30,500, "saleh Ali");
      trans.Execute();
      ChangeEmployeeUnionTransaction chngEmpUnion(empId, memberId, weeklyDues);
      chngEmpUnion.Execute();
      ChangeEmployeeUnionTransaction newChngEmpUnion(empId, newMemberId, newWeeklyDues);
      newChngEmpUnion.Execute();

      //Test Area
      Employee *myEmp = (PayrollDatabase::instance)->getEmployee(empId);
      UnionAffiliation *currentUF = ((UnionAffiliation*)(myEmp->unionAff));
      int testMemberId = currentUF->memberId;
      int testWeeklyDues = currentUF->weeklyDues;
   
      assert(testMemberId == newMemberId);
      assert(testWeeklyDues == newWeeklyDues);
      Employee *testOldMemberIdEmp = (PayrollDatabase::instance)->getEmployee((PayrollDatabase::instance)->getUnionMember(memberId));
     
    }
   void TestChangeEmployeeNoAffilicationTransaction() {
          int empId = generateEmployeeId();
       int weeklyDues = 500;
        std::string email = "test@gmail.com" + std::to_string(empId);
        int memberId = empId;
       //Add Employee Hourly Classification with  unionAffilication
             AddSalariedEmployeeTransaction trans(empId,"Mostafa",email ,30,500, "saleh Ali");
      trans.Execute();

      ChangeEmployeeUnionTransaction chngEmpUnion(empId, memberId, weeklyDues);
      chngEmpUnion.Execute();
      ChangeEmployeeNoUnionTransaction removeUF(empId);
 
      removeUF.Execute();
    //Test Area
    int x = (PayrollDatabase::instance)->getUnionMember(memberId);
    Employee *myEmp = (PayrollDatabase::instance)->getEmployee(empId);
    assert(x == -1);
    
   }  

   void TestPayDayTransactionForSalariedEmployee() {
    int monthlySalary = 500;
    int weeklyDues = 0;
    int empId = generateEmployeeId();
    std::string email = "test@gmail.com" + std::to_string(empId);
    PayDayTransaction payTrans(time(0));
    AddSalariedEmployeeTransaction trans(empId,"Mostafa" ,email, 30, monthlySalary, "saleh Ali");
    trans.Execute(); 
    payTrans.Execute();
      // Test Area
      PayCheck *pc = payTrans.getPayCheck(1);
      assert(pc != 0);
 
      assert(pc->deductions == 0);
      assert(pc->netPay == monthlySalary - weeklyDues);
      assert(pc->grossPay == monthlySalary);
   }
 
   void TestPayDayTransactionForHourlyEmployee() {
    int hourRate = 50;
    int weeklyDues = 300;
      int empId = generateEmployeeId();
      std::string email = "test@gmail.com" + std::to_string(empId);
      PayDayTransaction payTrans(time(0));
      AddHourlyEmployeeTransaction trans(empId, "Mostafa" ,email, 400, hourRate, "salehAli");
      trans.Execute();
      //Note Here we Put a TimeCard in the future to check date range (INVALID DATA )
      AddTimeCardTransaction tcs(empId, time(0) + (24 * 60 * 60), 13);
      tcs.Execute();
      AddTimeCardTransaction tcs2(empId, (time_t)(time(0) -  2 * (24 * 60 * 60)), 3);
      tcs2.Execute();
      AddTimeCardTransaction tcs3(empId, (time_t)(time(0) -  3 * (24 * 60 * 60)), 4);
      tcs3.Execute();
      AddTimeCardTransaction tcs4(empId, (time_t)(time(0) -  4 * (24 * 60 * 60)), 5);
      tcs4.Execute();
      AddTimeCardTransaction tcs5(empId, (time_t)(time(0) -  5 * (24 * 60 * 60)), 6);
      tcs5.Execute();
      float expectedSalary = (3 * hourRate) + (4 * hourRate) + (5 * hourRate) + (6 * hourRate);
      ChangeEmployeeUnionTransaction changeEmpUXN(empId, empId, weeklyDues);
      changeEmpUXN.Execute();

      payTrans.Execute();
      //Test Area
       PayCheck *pc = payTrans.getPayCheck(empId);
       assert(pc != 0);
       assert(pc->grossPay == expectedSalary);
   
       assert(pc->netPay == expectedSalary - pc->deductions);
       //Note this condition holds only if the employee has weekly schedule
       assert(pc->deductions == weeklyDues);
 
   }

   void TestPayDayTransactionForComissionEmployee() {
    int baseRate = 50;
    float comissionRate = 0.5;
    int weeklyDues = 300;
    int empId = generateEmployeeId();
    std::string email = "test@gmail.com" + std::to_string(empId);
    PayDayTransaction payTrans(time(0));
    AddComissionEmployeeTransaction addEmpTxn(empId,"Mostafa" ,email, 30, baseRate, comissionRate, "salehAli");
    addEmpTxn.Execute();
    AddSaleReceiptTransaction tcs(empId, time(0) + (24 * 60 * 60), 3);
    tcs.Execute();
    AddSaleReceiptTransaction tcs2(empId, (time_t)(time(0) -  2 * (24 * 60 * 60)), 3);
    tcs2.Execute();
    AddSaleReceiptTransaction tcs3(empId, (time_t)(time(0) -  3 * (24 * 60 * 60)), 3);
    tcs3.Execute();
    payTrans.Execute();

      //Test Area
       PayCheck *pc = payTrans.getPayCheck(empId);
       float expectedGrossPay = baseRate + (3 * comissionRate) + (3* comissionRate);
       assert(pc != 0);
       assert(expectedGrossPay == pc->grossPay); 
   }

    void TestServiecChargesAndWeeklyDuesDeductions() {

    int baseRate = 50;
    float comissionRate = 0.5;
    int weeklyDues = 300;
    int empId = generateEmployeeId();
    int memberId = empId;
    int serviceCharge = 20;
    int totalDeductions = serviceCharge + weeklyDues * 4;
    std::string email = "test@gmail.com" + std::to_string(empId);
    PayDayTransaction payTrans(time(0));
    AddComissionEmployeeTransaction addEmpTxn(empId,"Mostafa" ,email, 30, baseRate, comissionRate, "salehAli");
    ChangeEmployeeUnionTransaction changeEmpUXN(empId, memberId, weeklyDues);
    addEmpTxn.Execute();
    changeEmpUXN.Execute();
   
      //Add Some sale recipt he did (in which he will get his comission rate from it)
      AddSaleReceiptTransaction tcs(empId, time(0) + (24 * 60 * 60), 3);
      tcs.Execute();
      AddSaleReceiptTransaction tcs2(empId, (time_t)(time(0) -  2 * (24 * 60 * 60)), 3);
      tcs2.Execute();

    //Add Service charge due to his affiliation
    AddServiceChargeTransaction serviceChargeTrans(memberId, time(0), serviceCharge);
    serviceChargeTrans.Execute();

    //Run The Pay DAY
    payTrans.Execute();
      //Test Area
       PayCheck *pc = payTrans.getPayCheck(empId);
       assert(pc != 0);
       assert(pc->deductions == totalDeductions);

   }
 

  // void TestAddUF() {   
  //     int empId = 4;
  //     int memberId = 3;
  //     int weeklyDues = 10;
  //      AddEmpoloyeeTransaction* trans= new AddSalariedEmployeeTransaction (empId,"Mostafa" ,"test@gmail.com", 30, 500);
  //      trans->Execute();
  //      ChangeEmployeeUnionTransaction chng(empId, memberId, weeklyDues);
  //      chng.Execute();

  //      int returnedEmpId = PayrollDatabase::getUnionMember(memberId);

  //      assert(returnedEmpId == empId);
  // }

  // void TestRemoveUf() {   
  //     int empId = 4;
  //     int memberId = 3;
  //     int weeklyDues = 10;
  //      AddEmpoloyeeTransaction* trans= new AddSalariedEmployeeTransaction (empId,"Mostafa" ,"test@gmail.com", 30, 500);
  //      trans->Execute();
  //      ChangeEmployeeUnionTransaction chng(empId, memberId, weeklyDues);
  //      chng.Execute();
  //       ChangeEmployeeNoUnionTransaction remv(memberId);  
  //       remv.Execute();
  //   //    Employee*z = PayrollDatabase::getEmployee(empId);

  //   //    if (z==0) return;
  //   //      if (dynamic_cast<NoAffiliation *>(z->unionAff) != nullptr) {
  //   // // aPtr is instance of B
  //   //       std::cout << "Success";
  //   //   } else {
  //   // // aPtr is NOT instance of B
  //   //     std::cout << "Fail";
  //   //       }
  // }
  void ClearTables() {
    (PayrollDatabase::instance) -> ClearDatabase();
  }
};