//
// Created by Sebastian Brinch on 26/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H
#define BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H

#include <iostream>
#include <mysql.h>

class EmployeeOperations {

public:
    EmployeeOperations(const std::string& host = "localhost", const std::string& user = "", const std::string& password = "", const std::string& database = "");
    //~EmployeeOperations();

    void printAllCustomerAccounts();
    void createNewCustomer(std::string account_number, int balance, std::string email, int age, std::string firstname, std::string lastname);
    void createNewCustomerUser(std::string username, std::string password);
    void deleteCustomer();

private:
    std::unique_ptr<MYSQL, decltype(&mysql_close)>db_conn;
};

#endif //BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H
