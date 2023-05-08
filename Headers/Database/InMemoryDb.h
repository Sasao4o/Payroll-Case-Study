 #ifndef InMemoryDBHeader
 #define InMemoryDBHeader
#include <unordered_map>
#include "./Employee.h"
#include "./PayrollDatabase.h"
#include<vector>
namespace PayrollCaseStudy {
    namespace PayrollEMPDB {
class InMemoryDb : public PayrollDatabase {
 
     
    public:
 
    static std::unordered_map<int, Employee*> map;
    static std::unordered_map<int,int>memb_emp;
    
    void AddEmployee(int id, Employee* emp);
    Employee* getEmployee(int id);
    void DeleteEmployee(int id);
    void AddUnionMember(int memberId, Employee *emp);
    int getUnionMember(int memberId);
    void DeleteUnionMember(int memberId);
    std::vector<int> getEmployees();
    void AddSerivceCharge(Employee*emp, time_t time, int charge);
};
 

    }
}
 #endif