#include "../../Headers/Database/InMemoryDb.h"
#include "../../Headers/Affiliation/UnionAffiliation.h"
namespace PayrollCaseStudy {
    namespace PayrollEMPDB {  
        // InMemoryDb::InMemoryDb() : PayrollDatabase() {

        // }
     void InMemoryDb::AddEmployee(int id, Employee* emp) {
            map.insert({id,  emp});
            // map[id] = *emp;
           
    }
     Employee* InMemoryDb::getEmployee(int id) {
        //note this operator may lead to unexpected behaviour as it creats the object using default constructor if it doesn;t find it

        return map[id];
    }

     void InMemoryDb::AddUnionMember(int memberId, Employee *emp) { 
        memb_emp[memberId] = emp->id;
    }
           int InMemoryDb::getUnionMember(int memberId) {
            // return memb_emp[memberId];
             try {
                return memb_emp.at(memberId); 
             } 
             catch (std::out_of_range &e) {
                return -1;
             } 
    }
         std::vector<int> InMemoryDb::getEmployees() {
        std::vector<int> ids;
       std::unordered_map<int, Employee*>::iterator it;

        for (it = map.begin(); it != map.end(); it++)
        {
      
             ids.push_back(it->first);
        }
            return ids;
    }
      void InMemoryDb::DeleteUnionMember(int memberId) {
        memb_emp.erase(memberId);
    }
    void InMemoryDb::DeleteEmployee(int id) {
        map.erase(id);
    }
        void InMemoryDb::AddSerivceCharge(Employee*emp, time_t time, int charge) {
            //This not good also as UnionAffiliation is 
        PayrollCaseStudy::AffiliationBag::UnionAffiliation *uf = (PayrollCaseStudy::AffiliationBag::UnionAffiliation *)emp->unionAff;
        uf->addServiceCharge(time,charge);
           }
        std::unordered_map<int, Employee*> InMemoryDb::map;
        std::unordered_map<int, int> InMemoryDb::memb_emp;


    }
   
    
}