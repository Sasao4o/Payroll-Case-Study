add_library(
        Payroll_Test
        OBJECT
        PayrollTest.cpp
        SqlDbTest.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Test>
        PARENT_SCOPE)
