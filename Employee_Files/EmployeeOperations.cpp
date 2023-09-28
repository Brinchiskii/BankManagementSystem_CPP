//
// Created by Sebastian Brinch on 26/07/2023.
//

#include <iomanip>
#include <algorithm>
#include <random>
#include <iterator>
#include <cctype>


#include "EmployeeOperations.h"
#include "EmployeeAccount.h"
#include "../Logging/Logger.h"

Logger logger_employee("/Users/sebastianbrinch/CLionProjects/BankManagementSystem/Logging/Logs/logfile_employees.txt");

EmployeeOperations::EmployeeOperations(DatabaseConnectionManager &dbManager) : dbManager(dbManager) { }

void EmployeeOperations::printAllCustomerAccounts() {
    MYSQL* dbConnection = dbManager.getConnection();

    MYSQL_RES* rset;
    MYSQL_ROW rows;

    std::string sql = "SELECT * FROM Customers";

    if (mysql_query(dbConnection, sql.c_str())) {
        logger_employee.log(LogLevel::ERROR, "Failed to print all accounts" + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact Bank!";
        return;
    }

    rset = mysql_use_result(dbConnection);

    std::cout << std::left << std::setw(13) << std::setfill('-') << std::left << '+'
    << std::setw(9) << std::setfill('-') << std::left << '+'
    << std::setw(16) << std::setfill('-') << std::left << '+'
    << std::setw(10) << std::setfill('-') << std::left << '+'
    << std::setw(40) << std::setfill('-') << std::left << '+'
    << std::setw(5) << std::setfill('-') << std::left << '+'
    << std::setw(15) << std::setfill('-') << std::left << '+'
    << std::setw(15) << std::setfill('-') << std::left << '+' << '+' << std::endl;

    std::cout << std::setfill(' ') << '|' << std::left << std::setw(12) << "Customer ID"
    << std::setfill(' ') << '|' << std::setw(8) << "User ID"
    << std::setfill(' ') << '|' << std::setw(15) << "Account Number"
    << std::setfill(' ') << '|' << std::setw(9) << "Balance"
    << std::setfill(' ') << '|' << std::setw(39) << "Email"
    << std::setfill(' ') << '|' << std::setw(4) << "Age"
    << std::setfill(' ') << '|' << std::setw(14) << "First name"
    << std::setfill(' ') << '|' << std::setw(14) << "Last name" << '|' << std::endl;

    std::cout << std::left << std::setw(13) << std::setfill('-') << std::left << '+'
    << std::setw(9) << std::setfill('-') << std::left << '+'
    << std::setw(16) << std::setfill('-') << std::left << '+'
    << std::setw(10) << std::setfill('-') << std::left << '+'
    << std::setw(40) << std::setfill('-') << std::left << '+'
    << std::setw(5) << std::setfill('-') << std::left << '+'
    << std::setw(15) << std::setfill('-') << std::left << '+'
    << std::setw(15) << std::setfill('-') << std::left << '+' << '+' << std::endl;

    if(rset) {
        while ((rows = mysql_fetch_row(rset))) {
            std::cout << std::setfill(' ') << '|' << std::left << std::setw(12) << rows[0]
                    << std::setfill(' ') << '|' << std::setw(8) << rows[1]
                    << std::setfill(' ') << '|' << std::setw(15) << rows[2]
                    << std::setfill(' ') << '|' << std::setw(9) << rows[3]
                    << std::setfill(' ') << '|' << std::setw(39) << rows[4]
                    << std::setfill(' ') << '|' << std::setw(4) << rows[5]
                    << std::setfill(' ') << '|' << std::setw(14) << rows[6]
                    << std::setfill(' ') << '|' << std::setw(14) << rows[7] << '|' << std::endl;
        }
        std::cout << std::left << std::setw(13) << std::setfill('-') << std::left << '+'
                  << std::setw(9) << std::setfill('-') << std::left << '+'
                  << std::setw(16) << std::setfill('-') << std::left << '+'
                  << std::setw(10) << std::setfill('-') << std::left << '+'
                  << std::setw(40) << std::setfill('-') << std::left << '+'
                  << std::setw(5) << std::setfill('-') << std::left << '+'
                  << std::setw(15) << std::setfill('-') << std::left << '+'
                  << std::setw(15) << std::setfill('-') << std::left << '+' << '+' << std::endl;
    }

    mysql_free_result(rset);
}

void EmployeeOperations::createNewCustomerUser(std::string username, std::string password) {
    MYSQL* dbConnection = dbManager.getConnection();

    std::string sql = "INSERT INTO Users(username, password, role) VALUES('" + username + "', '" + password + "', 'Customer')";

    if(!mysql_query(dbConnection, sql.c_str())) {
        logger_employee.log(LogLevel::INFO, "Created new customer user:" + std::string(username));
        std::cout << "Created new customer user: " << username << std::endl;
    } else {
        logger_employee.log(LogLevel::ERROR, "Failed to create new customer: " + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact administration!" << std::endl;
    }
}

void EmployeeOperations::createNewCustomer(std::string account_number, std::string email, int age, std::string firstname, std::string lastname, std::string password) {
    MYSQL* dbConnection = dbManager.getConnection();
    MYSQL_RES *rset;
    MYSQL_ROW row;
    int usr_id{};

    // Get the username:
    char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                       'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                       's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int last_c{};
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::shuffle(std::begin(letters), std::end(letters), std::mt19937(seed));

    char randomLetter = std::toupper(letters[0]);

    //std::string username{static_cast<char>(firstname[0] + lastname[0] + letters[0])};
    std::string username{firstname.substr(0, 1) + lastname.substr(0, 1) + randomLetter};

    // Creating the new customer user account
    createNewCustomerUser(username, password);

    // Getting the newest user in the users table which needs to be associated with the customer table
    std::string queryUsersTable = "SELECT * FROM Users ORDER BY user_id DESC LIMIT 1";
    if(!mysql_query(dbConnection, queryUsersTable.c_str())) {
        rset = mysql_use_result(dbConnection);
        if(rset) {
            row = mysql_fetch_row(rset);
            if(row) {
                usr_id = strtol(row[0], nullptr, 10);
            }
            mysql_free_result(rset);
        }
    }

    std::string sql = "INSERT INTO Customers (user_id, account_number, balance, email, age, firstname, lastname) VALUES(" + std::to_string(usr_id) + ",'" + account_number
            + "'," + std::to_string(0) + ",'" + email + "'," + std::to_string(age) + ",'" + firstname + "','" + lastname + "')";

    if(!mysql_query(dbConnection, sql.c_str())) {
        logger_employee.log(LogLevel::INFO, "Created new customer: " + std::string(firstname) + " " + std::string(lastname));
        std::cout << "Created new customer: " << firstname << " " << lastname << std::endl;
    } else {
        logger_employee.log(LogLevel::ERROR, "Failed to create new customer: " + std::string(mysql_error(dbConnection)));
        std::cout << "Error: Contact administration!" << std::endl;
    }
}

void EmployeeOperations::deleteCustomer(int account_number) {
    MYSQL* dbConnection = dbManager.getConnection();

    std::string sql = "DELETE FROM Customers WHERE customer_id='" + std::to_string(account_number) + "'";

    if(!mysql_query(dbConnection, sql.c_str())) {
        logger_employee.log(LogLevel::INFO, "Deleted customer account: " + std::to_string(account_number));
        std::cout << "Deleted customer account: " << account_number << std::endl;
    } else {
        logger_employee.log(LogLevel::ERROR, "Failed to delete customer: " + std::to_string(account_number) + std::string(
                mysql_error(dbConnection)));
        std::cout << "Error: Contact administration!" << std::endl;
    }
}