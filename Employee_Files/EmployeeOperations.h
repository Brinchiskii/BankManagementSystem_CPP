//
// Created by Sebastian Brinch on 26/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H
#define BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H

#include <iostream>
#include <mysql.h>

#include "../DatabaseConnectionManager.h"


class EmployeeOperations {

public:
    EmployeeOperations(DatabaseConnectionManager& dbManager);

    void printAllCustomerAccounts();
    void createNewCustomer(std::string account_number, std::string email, int age, std::string firstname, std::string lastname, std::string password);
    void createNewCustomerUser(std::string username, std::string password);
    void deleteCustomer(int account_number);

    // ONLY FOR ADMINISTRATION
    void createNewEmployeeUser();
    void createNewEmployee();
    void deleteEmployee();

private:
    DatabaseConnectionManager& dbManager;
};

#endif //BANKMANAGEMENTSYSTEM_EMPLOYEEOPERATIONS_H
