//
// Created by Sebastian Brinch on 24/07/2023.
//
#include <iostream>

#include "CustomerOperations.h"
#include "CustomerAccount.h"
#include "../Logging/Logger.h"

Logger logger_customer("/Users/sebastianbrinch/CLionProjects/BankManagementSystem/Logging/Logs/logfile_customer.txt");

CustomerOperations::CustomerOperations(DatabaseConnectionManager &dbManager) : dbManager(dbManager) {}

/*
 * FUNCTION FOR GETTING ACCOUNT INFORMATION
 */

std::unique_ptr<CustomerAccount> CustomerOperations::getCustomerAccount(int customer_id) {
    MYSQL* dbConnection = dbManager.getConnection();

    std::unique_ptr<CustomerAccount> customerAccount = std::make_unique<CustomerAccount>();
    MYSQL_RES *rset;
    MYSQL_ROW row;

    std::string sql = "SELECT * FROM Customers WHERE customer_id=" + std::to_string(customer_id);

    if (!mysql_query(dbConnection, sql.c_str())) {
        //std::cout << "Query successful." << std::endl;
        logger_customer.log(LogLevel::INFO, "Query of CUSTOMERS successful.");
        rset = mysql_use_result(dbConnection);
        if (rset) {
            row = mysql_fetch_row(rset);
            if (row) {
                customerAccount = std::make_unique<CustomerAccount>();
                customerAccount->setUserId(strtol(row[1], nullptr, 10));
                customerAccount->setAccountNumber(row[2]);
                customerAccount->setBalanceCents(strtol(row[3], nullptr, 10));
                customerAccount->setEmail(row[4]);
                customerAccount->setAge(strtol(row[5], nullptr, 10));
                customerAccount->setFirstName(row[6]);
                customerAccount->setLastName(row[7]);
            }
            mysql_free_result(rset);
        } else {
            logger_customer.log(LogLevel::ERROR, "Unable to retrieve result set: " + std::string(mysql_error(dbConnection)));
            std::cout << "Error: Contact bank!" << std::endl;
        }
    } else {
        logger_customer.log(LogLevel::ERROR, "Query of CUSTOMERS failed: " + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact bank!" << std::endl;
    }

    return customerAccount;
}

/*
 *  FUNCTION FOR WITHDRAWAL OF MONEY
 */

void CustomerOperations::withdraw(int accountNumber, double amount) {
    //CustomerAccount* c_acc = getCustomerAccount(accountNumber);
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(accountNumber);

    MYSQL* dbConnection = dbManager.getConnection();

    if(!customerAccount) {
        logger_customer.log(LogLevel::WARNING, "Customer account not found.");
        std::cout << "Customer account not found." << std::endl;
        return;
    }

    if (amount <= 0) {
        logger_customer.log(LogLevel::WARNING, "Invalid withdrawal amount: " + std::to_string(amount));
        std::cout << "Invalid withdrawal amount. Amount must be greater than 0." << std::endl;
    }

    if(amount > customerAccount->getBalanceInDollars()) {
        logger_customer.log(LogLevel::WARNING, "Insufficient balance, withdraw amount to high: " + std::to_string(amount));
        std::cout << "Insufficient balance, cannot withdraw higher amount than your balance." << std::endl;
        return;
    }

    // Withdrawal calculations
    customerAccount->setBalanceCents(customerAccount->getBalanceCents() - static_cast<int>(amount * 100));

    // Updating the database with the new balance
    std::string sql = "UPDATE Customers SET balance=" + std::to_string(customerAccount->getBalanceCents()) + " WHERE account_number='" + customerAccount->getAccountNumber() + "'";

    if(!mysql_query(dbConnection, sql.c_str())) {
        logger_customer.log(LogLevel::INFO, "Withdrawal successful.");
        std::cout << "Withdrawal successful. New balance: $" << customerAccount->getBalanceInDollars() << std::endl;
    } else {
        logger_customer.log(LogLevel::ERROR, "Updating balance failed: " + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact bank!" << std::endl;
    }
}

/*
 * FUNCTION FOR DEPOSIT MONEY TO ACCOUNT
 */

void CustomerOperations::deposit(int accountNumber, double amount) {
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(accountNumber);

    MYSQL* dbConnection = dbManager.getConnection();

    if(!customerAccount) {
        logger_customer.log(LogLevel::WARNING, "Customer account not found.");
        std::cout << "Error: Customer account not found." << std::endl;
        return;
    }

    if (amount <= 0) {
        logger_customer.log(LogLevel::WARNING, "Invalid deposit amount: " + std::to_string(amount));
        std::cout << "Invalid deposit amount. Amount must be greater than 0." << std::endl;
    }

    customerAccount->setBalanceCents(customerAccount->getBalanceCents() + static_cast<int>(amount * 100));

    std::string sql = "UPDATE Customers SET balance=" + std::to_string(customerAccount->getBalanceCents()) + " WHERE account_number='" + customerAccount->getAccountNumber() + "'";

    if(!mysql_query(dbConnection, sql.c_str())) {
        logger_customer.log(LogLevel::INFO, "Deposit successful.");
        std::cout << "Deposit successful. New balance: $" << customerAccount->getBalanceInDollars() << std::endl;
    } else {
        logger_customer.log(LogLevel::ERROR, "Updating balance failed. " + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact bank!" << std::endl;
    }
}

/*
 * Function for showing account details of the specific customer
 */

void CustomerOperations::showAccountDetails(int customerId) {
    std::unique_ptr<CustomerAccount> customerAccount = getCustomerAccount(customerId);

    MYSQL* dbConnection = dbManager.getConnection();

    if(!customerAccount) {
        logger_customer.log(LogLevel::WARNING, "Customer account not found.");
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