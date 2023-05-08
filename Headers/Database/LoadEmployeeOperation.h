#ifndef LoadEmployeeHeader 
#define LoadEmployeeHeader
#include<string>
#include "./Employee.h"
#include "./sqlite3.h"
#include<string.h>
namespace PayrollCaseStudy {

    namespace PayrollEMPDB {
      using PayrollCaseStudy::SchedulesBag::PaymentSchedule;
      using PayrollCaseStudy::Classification::PayClassification;
      using PayrollCaseStudy::MethodsBag::PayMethod;
     using  PayrollCaseStudy::AffiliationBag::Affiliation;
class LoadEmployeeOperation {
    public:
       struct EmployeeRecord {
          int empId = -1;
          std::string name;
          std::string email;
          std::string address;
          int age;
          std::string ScheduleType;
          std::string PaymentMethodType;
          std::string PaymentClassificationType;
      };
            struct AffiliationRecord {
          int dues;
      };
    //Helpers Datamember for the functions
    LoadEmployeeOperation(int id, sqlite3*db);
    sqlite3* DatabaseConnection;
    int id;
    std::string methodCode;
    
    static int injectEmployeeData(void *data, int numberOfColumns, char** rowData, char** columnNames);     
    static int injectComissionPayClass(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int  injectHourlyPayClass (void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectMonthlyPayClass(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectDirectPayMethod(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectMailPayMethod(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectAffiliationId(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectAffiliation(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectMemberId(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectServiceCharge(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectSaleRecipt(void *data, int numberOfColumns, char** rowData, char** columnNames);
        static int injectTimeCard(void *data, int numberOfColumns, char** rowData, char** columnNames);
     void Execute();
     Employee* getEmployee();
    void LoadServiceCharge(int , Affiliation*);
        void LoadEmployeeClassificationData(std::string type, PayClassification*payClass);
     private:
      Employee* emp = 0;
        PaymentSchedule * LoadEmployeeSchedule(std::string);
        PayClassification * LoadEmployeeClassification(std::string);
        PayMethod*  LoadEmployeeMethod(std::string);
        int  LoadAffiliationId(int);
        int LoadMemberId(int);
        Affiliation * LoadAffiliation(int memberId, int dues);
};
    }
}
 

#endif