//
// Created by Sebastian Brinch on 24/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H
#define BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H

#include <mysql.h>
#include <string>
#include <memory>

#include "../DatabaseConnectionManager.h"

class CustomerAccount;

class CustomerOperations {

public:
    CustomerOperations(DatabaseConnectionManager& dbManager);

    void deposit(int accountNumber, double amount);
    void withdraw(int accountNumber, double amount);
    std::unique_ptr<CustomerAccount> getCustomerAccount(int customer_id);
    void showAccountDetails(int customerId);

private:
    DatabaseConnectionManager& dbManager;
};

#endif //BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H
