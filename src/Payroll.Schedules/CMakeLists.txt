add_library(
        Payroll_Schedules
        OBJECT
        MonthlyPaymentSchedule.cpp
        WeeklyPaymentSchedule.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Schedules>
        PARENT_SCOPE)
