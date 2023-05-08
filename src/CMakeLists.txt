add_subdirectory(Payroll.Affiliation)
add_subdirectory(Payroll.Application)
add_subdirectory(Payroll.Classification)
add_subdirectory(Payroll.Database)
add_subdirectory(Payroll.Methods)
add_subdirectory(Payroll.Pay)
add_subdirectory(Payroll.Schedules)
add_subdirectory(Payroll.Transaction)
add_library(Payroll STATIC ${ALL_OBJECT_FILES})
set(Payroll_Libs 
    Payroll_Application
    Payroll_Affiliation
    Payroll_Classification
    Payroll_Database
    Payroll_Methods
    Payroll_Pay
    Payroll_Schedules
    Payroll_Transaction
)

set(Payroll_TestFiles 
Payroll_Test)

target_link_libraries(Payroll ${Payroll_Libs} ${Payroll_TestFiles})
 