cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(PayrollProject VERSION 1.0 DESCRIPTION "This Payroll Project Using C++ OOP Paradigm")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

 
 # includes
set(PAYROLL_HEADERS ${PROJECT_SOURCE_DIR}/Headers)
include_directories(${PAYROLL_HEADERS})
add_subdirectory(src)
add_subdirectory(Test)
add_executable(PayrollProject x.cpp)
target_link_libraries(PayrollProject PUBLIC Payroll Payroll_Test )
target_link_libraries(PayrollProject LINK_PUBLIC -ldl -pthread)

 
