add_library(
        Payroll_Classification
        OBJECT
        ComissionPayClassification.cpp
        HourlyPayClassification.cpp
        MonthlyPayClassification.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Classification>
        PARENT_SCOPE)
