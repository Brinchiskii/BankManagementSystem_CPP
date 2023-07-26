cmake_minimum_required(VERSION 3.25)
project(BankManagementSystem)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

# Set the path to the MySQL Connector/C++ directory
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/local/mysql-8.0.33-macos13-arm64")

# Set the path to the MySQL Connector/C++ include directory
set(MYSQL_INCLUDE_DIR "${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include")

# Set the path to the MySQL Connector/C++ libraries directory
set(MYSQL_LIB_DIR "${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib")

# Add the MySQL Connector/C++ include directory to the include path
include_directories(${MYSQL_INCLUDE_DIR})

# Add the MySQL Connector/C++ libraries directory to the link path
link_directories(${MYSQL_LIB_DIR})

add_executable(BankManagementSystem main.cpp Employee_Files/EmployeeAccount.cpp Employee_Files/EmployeeAccount.h Customer_Files/CustomerAccount.cpp Customer_Files/CustomerAccount.h Customer_Files/CustomerOperations.cpp Customer_Files/CustomerOperations.h Employee_Files/EmployeeOperations.cpp Employee_Files/EmployeeOperations.h)

# Link the necessary libraries
target_link_libraries(BankManagementSystem libmysqlclient.dylib)
