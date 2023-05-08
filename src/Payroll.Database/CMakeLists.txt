add_library(
        Payroll_Database
        OBJECT
        DeleteAffiliationOperation.cpp
        Employee.cpp
        InMemoryDb.cpp
        LoadEmployeeOperation.cpp
        PayrollDatabase.cpp
        SaveAffiliationOperation.cpp
        SaveEmployeeOperation.cpp
        SaveSaleReceiptOperation.cpp
        SaveServiceChargeOperation.cpp
        SaveTimeCardOperation.cpp
        SqlDb.cpp
        sqlite3.c
        UpdatePayClassificationOperation.cpp
        UpdatePayMethodOperation.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Database>
        PARENT_SCOPE)
