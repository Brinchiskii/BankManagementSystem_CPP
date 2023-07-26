//
// Created by Sebastian Brinch on 24/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H
#define BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H

#include <mysql.h>
#include <string>
#include <memory>

class CustomerAccount;

class CustomerOperations {

public:
    explicit CustomerOperations(const std::string& host = "localhost", const std::string& user = "", const std::string& password = "", const std::string& database = "");
    ~CustomerOperations();

    void deposit(int accountNumber, double amount);
    void withdraw(int accountNumber, double amount);
    std::unique_ptr<CustomerAccount> getCustomerAccount(int customer_id);
    void showAccountDetails(int customerId);

private:
    // Smart pointer for MsySQL connection
    std::unique_ptr<MYSQL, decltype(&mysql_close)> db_conn;
};

#endif //BANKMANAGEMENTSYSTEM_CUSTOMEROPERATIONS_H
