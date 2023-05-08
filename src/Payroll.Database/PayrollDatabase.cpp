#include "../../Headers/Database/PayrollDatabase.h"

namespace PayrollCaseStudy {
    namespace PayrollEMPDB {

        // PayrollDatabase::PayrollDatabase(PayrollDatabase *db) {
        //     this->instance = db;
        // }
    //  void PayrollDatabase::AddEmployee(int id, Employee* emp) {
    //         map.insert({id,  emp});
    //         // map[id] = *emp;
           
    // }
    //  Employee* PayrollDatabase::getEmployee(int id) {
    //     //note this operator may lead to unexpected behaviour as it creats the object using default constructor if it doesn;t find it

    //     return map[id];
    // }

    //  void PayrollDatabase::AddUnionMember(int memberId, Employee *emp) {
    //     memb_emp[memberId] = emp->id;
    // }
    //        int PayrollDatabase::getUnionMember(int memberId) {
    //         // return memb_emp[memberId];
    //          try {
    //             return memb_emp.at(memberId); 
    //          } 
    //          catch (std::out_of_range &e) {
    //             return -1;
    //          } 
    // }
    //      std::vector<int> PayrollDatabase::getEmployees() {
    //     std::vector<int> ids;
    //    std::unordered_map<int, Employee*>::iterator it;

    //     for (it = map.begin(); it != map.end(); it++)
    //     {
      
    //          ids.push_back(it->first);
    //     }
    //         return ids;
    // }
    //   void PayrollDatabase::DeleteUnionMember(int memberId) {
    //     memb_emp.erase(memberId);
    // }
    //     std::unordered_map<int, Employee*> PayrollDatabase::map;
    //     std::unordered_map<int, int> PayrollDatabase::memb_emp;


    }
   
    
}