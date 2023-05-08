 #ifndef PayDatabaseHeader
 #define PayDatabaseHeader
#include <unordered_map>
#include "./Employee.h"
#include<vector>
namespace PayrollCaseStudy {
    namespace PayrollEMPDB {
class PayrollDatabase {
 
     
    public:
    static PayrollDatabase* instance;
    virtual void ClearDatabase() = 0;
    virtual void AddEmployee(int id, Employee* emp) = 0;
    virtual Employee* getEmployee(int id) = 0;
    virtual void DeleteEmployee(int id) = 0;
    virtual void AddUnionMember(int memberId, Employee *emp) = 0;
    virtual int getUnionMember(int memberId) = 0;
    virtual void DeleteUnionMember(int memberId) = 0;
    virtual std::vector<int> getEmployees() = 0;
    virtual void AddSerivceCharge(Employee*emp, time_t time, int charge) = 0;
    virtual void AddTimeCard(Employee*emp, time_t time, int hours) = 0;
    virtual void AddSaleReceipt(Employee *emp, time_t, float amount) = 0;
    virtual   void UpdateEmployee(int id, std::string key, std::string value) = 0;
    virtual void UpdateEmpPayMethod(int id, PayrollCaseStudy::MethodsBag::PayMethod*payMethod) = 0;
    virtual void UpdateEmpPaySchedule(int id, PayrollCaseStudy::SchedulesBag::PaymentSchedule*paySchedule) = 0;
    virtual void UpdateEmpPayClass(int id, PayrollCaseStudy::Classification::PayClassification*payClass) = 0;
};
 

    }
}
 #endif