add_library(
        Payroll_Affiliation
        OBJECT
        Affiliation.cpp
        NoAffiliation.cpp
        UnionAffiliation.cpp
        )

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:Payroll_Affiliation>
        PARENT_SCOPE)
