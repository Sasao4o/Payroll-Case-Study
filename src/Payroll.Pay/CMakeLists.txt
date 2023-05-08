add_library(
        Payroll_Pay
        OBJECT
        PayCheck.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Pay>
        PARENT_SCOPE)
