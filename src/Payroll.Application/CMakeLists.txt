add_library(
        Payroll_Application
        OBJECT
        main.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Application>
        PARENT_SCOPE)
