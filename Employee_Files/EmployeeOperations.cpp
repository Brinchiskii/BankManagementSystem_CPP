//
// Created by Sebastian Brinch on 26/07/2023.
//

#include <iomanip>
#include <algorithm>


#include "EmployeeOperations.h"
#include "EmployeeAccount.h"

EmployeeOperations::EmployeeOperations(const std::string &host, const std::string &user, const std::string &password,
                                       const std::string &database): db_conn(mysql_init(nullptr), &mysql_close) {

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

void EmployeeOperations::printAllCustomerAccounts() {
    MYSQL_RES* rset;
    MYSQL_ROW rows;

    std::string sql = "SELECT * FROM Customers";

    if (mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Error printing all accounts!";
        return;
    }

    rset = mysql_use_result(db_conn.get());

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
    std::string sql = "INSERT INTO Users(username, password, role) VALUES('" + username + "', '" + password + "', 'Customer')";

    if(!mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Created new customer user: " << username << std::endl;
    } else {
        std::cout << "Failed to create new customer: " << username << std::endl;
        const char* error_message = mysql_error(db_conn.get());
        std::cout << "MySQL Error Message: " << error_message << std::endl;
    }
}

void EmployeeOperations::createNewCustomer(std::string account_number, int balance, std::string email, int age, std::string firstname, std::string lastname) {

    MYSQL_RES *rset;
    MYSQL_ROW row;
    int usr_id{};

    // Getting the newest user in the users table which needs to be associated with the customer table
    std::string queryUsersTable = "SELECT * FROM Users ORDER BY user_id DESC LIMIT 1";
    if(!mysql_query(db_conn.get(), queryUsersTable.c_str())) {
        rset = mysql_use_result(db_conn.get());
        if(rset) {
            row = mysql_fetch_row(rset);
            if(row) {
                usr_id = strtol(row[0], nullptr, 10);
            }
            mysql_free_result(rset);
        }
    }

    std::string sql = "INSERT INTO Customers (user_id, account_number, balance, email, age, firstname, lastname) VALUES(" + std::to_string(usr_id) + ",'" + account_number
            + "'," + std::to_string(balance) + ",'" + email + "'," + std::to_string(age) + ",'" + firstname + "','" + lastname + "')";

    if(!mysql_query(db_conn.get(), sql.c_str())) {
        std::cout << "Created new customer: " << firstname << " " << lastname << std::endl;
    } else {
        std::cout << "Failed to create new customer: " << firstname << " " << lastname << std::endl;
        const char* error_message = mysql_error(db_conn.get());
        std::cout << "MySQL Error Message: " << error_message << std::endl;
    }
}

