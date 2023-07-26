//
// Created by Sebastian Brinch on 24/07/2023.
//
#include <iostream>

#include "CustomerOperations.h"
#include "CustomerAccount.h"

CustomerOperations::CustomerOperations(const std::string &host, const std::string &user, const std::string &password, const std::string &database)
    : db_conn(mysql_init(nullptr), &mysql_close) {

    if(!db_conn) {
        std::cout << "MySQL initialization failed!" << std::endl;
        throw std::runtime_error("Runtime: MySQL Initialization failed!");
    }

    MYSQL* mysql_conn = mysql_real_connect(db_conn.get(), host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0);

    if (mysql_conn) {
        // Connection successful, reset the unique pointer with the valid connection.
        //db_conn.reset(mysql_conn);
        std::cout << "You are now logged in as: " << user << '\n';
    } else {
        // Connection failed, handle the error.
        std::cout << "Connection Error: " << mysql_error(db_conn.get()) << std::endl;
        throw std::runtime_error("Connection Error!");
        // Or use std::cerr to print the error message to the standard error stream.
        // std::cerr << "Connection Error: " << mysql_error(db_conn.get()) << std::endl;
    }
}

std::unique_ptr<CustomerAccount> CustomerOperations::getCustomerAccount(int customer_id) {
    // ... (your existing code)

    std::unique_ptr<CustomerAccount> customer;
    MYSQL_RES *rset;
    MYSQL_ROW row;

    std::string sql = "SELECT * FROM Customers WHERE customer_id=" + std::to_string(customer_id);

    if (!mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Query successful." << std::endl;
        rset = mysql_use_result(db_conn.get());
        if (rset) {
            row = mysql_fetch_row(rset);
            if (row) {
                customer = std::make_unique<CustomerAccount>();
                customer->setUserId(strtol(row[1], nullptr, 10));
                customer->setAccountNumber(row[2]);
                customer->setBalanceCents(strtol(row[3], nullptr, 10));
                customer->setEmail(row[4]);
                customer->setAge(strtol(row[5], nullptr, 10));
                customer->setFirstName(row[6]);
                customer->setLastName(row[7]);
            }
            mysql_free_result(rset);
        } else {
            std::cout << "Error: Unable to retrieve result set." << std::endl;
            const char* error_message = mysql_error(db_conn.get());
            std::cout << "MySQL Error Message: " << error_message << std::endl;
        }
    } else {
        std::cout << "Query failed." << std::endl;
        const char* error_message = mysql_error(db_conn.get());
        std::cout << "MySQL Error Message: " << error_message << std::endl;
    }

    //std::unique_ptr<CustomerAccount> customerPtr(customer);
    return std::move(customer);
}

void CustomerOperations::withdraw(int accountNumber, double amount) {
    //CustomerAccount* c_acc = getCustomerAccount(accountNumber);
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(accountNumber);


    if(!customerAccount) {
        std::cout << "Error: Customer account not found." << std::endl;
        return;
    }

    if (amount <= 0) {
        std::cout << "Error: Invalid withdrawal amount. Amount must be greater than 0." << std::endl;
    }

    if(amount > customerAccount->getBalanceInDollars()) {
        std::cout << "Error: Insufficient balance." << std::endl;
        return;
    }

    // Withdrawal calculations
    customerAccount->setBalanceCents(customerAccount->getBalanceCents() - static_cast<int>(amount * 100));

    // Updating the database with the new balance
    std::string sql = "UPDATE Customers SET balance=" + std::to_string(customerAccount->getBalanceCents()) + " WHERE account_number='" + customerAccount->getAccountNumber() + "'";

    if(!mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Withdrawal successful. New balance: $" << customerAccount->getBalanceInDollars() << std::endl;
    } else {
        std::cout << "Error updating balance in the database." << std::endl;
        const char* error_message = mysql_error(db_conn.get());
        std::cout << "MySQL Error Message: " << error_message << std::endl;
    }
}

void CustomerOperations::deposit(int accountNumber, double amount) {
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(accountNumber);

    if(!customerAccount) {
        std::cout << "Error: Customer account not found." << std::endl;
        return;
    }

    if (amount <= 0) {
        std::cout << "Error: Invalid deposit amount. Amount must be greater than 0." << std::endl;
    }

    customerAccount->setBalanceCents(customerAccount->getBalanceCents() + static_cast<int>(amount * 100));

    std::string sql = "UPDATE Customers SET balance=" + std::to_string(customerAccount->getBalanceCents()) + " WHERE account_number='" + customerAccount->getAccountNumber() + "'";

    if(!mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Deposit successful. New balance: $" << customerAccount->getBalanceInDollars() << std::endl;
    } else {
        std::cout << "Error updating balance in the database." << std::endl;
        const char* error_message = mysql_error(db_conn.get());
        std::cout << "MySQL Error Message: " << error_message << std::endl;
    }
}

void CustomerOperations::showAccountDetails(int customerId) {
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(customerId);

    if(!customerAccount) {
        std::cout << "Error: Customer account not found." << std::endl;
        return;
    }

    if(customerAccount != nullptr) {
        std::cout << "Customer ID: " << customerId << std::endl;
        std::cout << "User ID: " << customerAccount->getUserId() << std::endl;
        std::cout << "Account Number: " << customerAccount->getAccountNumber() << std::endl;
        std::cout << "Balance: $" << customerAccount->getBalanceInDollars() << std::endl;
        std::cout << "Email: : " << customerAccount->getEmail() << std::endl;
        std::cout << "Age: " << customerAccount->getAge() << std::endl;
        std::cout << "First name: " << customerAccount->getFirstName() << std::endl;
        std::cout << "Last name: " << customerAccount->getLastName() << std::endl;
    }
}

CustomerOperations::~CustomerOperations() {

}