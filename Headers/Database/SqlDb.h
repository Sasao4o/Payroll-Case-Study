 #ifndef SqlDbHeader
 #define SqlDbHeader
#include <unordered_map>
#include "./Employee.h"
#include "./PayrollDatabase.h"
#include "./SaveEmployeeOperation.h"
#include "./LoadEmployeeOperation.h"
#include "./SaveAffiliationOperation.h"
 #include "./SaveServiceChargeOperation.h"
  #include "./UpdatePayMethodOperation.h"
  #include "./UpdatePayClassificationOperation.h"
  #include "./SaveTimeCardOperation.h"
    #include "./SaveSaleReceiptOperation.h"
    #include "./DeleteAffiliationOperation.h"
#include<vector>
#include "./sqlite3.h"

namespace PayrollCaseStudy {
    namespace PayrollEMPDB {

    // struct EmployeeRecord {
    //       int empId;
    //       std::string name;
    //     
    //       std::string email;
    //       int address;
    //       int age;
    //       std::string ScheduleType;
    //       std::string PaymentMethodType;
    //       std::string PaymentClassificationType;
    //   } empRecord;
class SqlDb : public PayrollDatabase {
 
     
    public:
 
 
    SqlDb();
    void AddEmployee(int id, Employee* emp);
    Employee* getEmployee(int id);
    void DeleteEmployee(int id);
    void AddUnionMember(int memberId, Employee *emp);
    int getUnionMember(int memberId);
    void DeleteUnionMember(int memberId);
    std::vector<int> getEmployees();
    std::string getScheduleKey(PayrollCaseStudy::SchedulesBag::PaymentSchedule *paySchedule);
    std::string getPayClassificationKey(PayrollCaseStudy::Classification::PayClassification *payClass);
    std::string getPayMethodKey(PayrollCaseStudy::MethodsBag::PayMethod *payMethod);
    std::string quotesql( const std::string& s );
    void AddSerivceCharge(Employee*emp, time_t time, int charge);
     void AddTimeCard(Employee*emp, time_t time, int charge);
     void AddSaleReceipt(Employee *emp, time_t, float amount);
      void  UpdateEmployee(int id, std::string key, std::string value);
      void UpdateEmpPayMethod(int id, PayrollCaseStudy::MethodsBag::PayMethod* payMethod);
     void UpdateEmpPaySchedule(int id, PayrollCaseStudy::SchedulesBag::PaymentSchedule*paySchedule);
    void UpdateEmpPayClass(int id, PayClassification *payClass);
    private:
    sqlite3* DatabaseConnection = 0;
    //This Partition is datamember to communicate between process 
    //its purpose to concentrat OCP in one methdo inestead of spreading the violation in the code
    std::string methodCode;
    std::string classificationCode;
    
    std::string insertPaymentMethodQuery;
    std::string insertClassificationQuery;
    //END
    void ClearDatabase();
    void fetchPaymentMethod(std::string code, int id);
    void fetchScheduleType(std::string code, int id);
    void fetchClassificationType(std::string code, int id);
    static int injectEmployeeData(void *data, int numberOfColumns, char** rowData, char** columnNames);
    static int injectEmployeeId(void *data, int numberOfColumns, char** rowData, char** columnNames);
     static int injectEmployeesId(void *data, int numberOfColumns, char** rowData, char** columnNames);
};
 

    }
}
 #endif