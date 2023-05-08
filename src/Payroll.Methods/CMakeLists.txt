add_library(
        Payroll_Methods
        OBJECT
        DirectPayMethod.cpp
        HoldPayMethod.cpp
        MailPayMethod.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Methods>
        PARENT_SCOPE)
