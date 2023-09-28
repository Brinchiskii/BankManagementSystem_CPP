#include <iostream>
#include <mysql.h>
#include <string>
#include <stdlib.h>

// Inclusion of header files
#include "Employee_Files/EmployeeAccount.h"
#include "Customer_Files/CustomerOperations.h"
#include "Employee_Files/EmployeeOperations.h"
#include "DatabaseConnectionManager.h"
#include "LoginManager.h"
#include "Logging/Logger.h"


int main() {
    DatabaseConnectionManager dbManager;

    Logger logger("/Users/sebastianbrinch/CLionProjects/BankManagementSystem/Logging/Logs/logfile.txt");

    // MySQL Server
    std::string host = "";
    std::string user = "";
    std::string dbpassword = "";
    std::string database = "";


    if (dbManager.connect(host, user, dbpassword, database)) {
        LoginManager loginManager(dbManager);


        while(1) {
            std::cout << "Enter your username: ";
            std::string username;
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::string password;
            std::cin >> password;

            LoginManager::UserRole role;
            LoginManager::UserRole userRole = loginManager.login(username, password, role);

            if (userRole == LoginManager::UserRole::Customer) {
                CustomerOperations customerOperations(dbManager);
                std::cout << "Logged in as customer!" << std::endl;
                // Call customer-specific functions here
                int choice{}, amount{}, customerid{};

                while (1) {
                    std::cout << "Menu Options" << std::endl
                              << "1 - Show account details" << std::endl
                              << "2 - Deposit" << std::endl
                              << "3 - Withdraw" << std::endl
                              << "4 - Log out" << std::endl
                              << "Choose: ";
                    std::cin >> choice;

                    if (choice == 4) {
                        std::cout << "Logging out..." << std::endl;
                        break;
                    }

                    switch (choice) {
                        case 1:
                            std::cout << "Enter customer ID: ";
                            std::cin >> customerid;
                            customerOperations.showAccountDetails(customerid);
                            break;
                        case 2:
                            std::cout << "Enter amount you want to deposit: ";
                            std::cin >> amount;
                            std::cout << "Enter customer ID: ";
                            std::cin >> customerid;
                            customerOperations.deposit(customerid, amount);
                            break;
                        case 3:
                            std::cout << "Enter amount you want to withdraw: ";
                            std::cin >> amount;
                            std::cout << "Enter customer ID: ";
                            std::cin >> customerid;
                            customerOperations.withdraw(customerid, amount);
                            break;
                    }
                }
            } else if (userRole == LoginManager::UserRole::Employee) {
                EmployeeOperations employeeOperations(dbManager);
                std::cout << "Logged in as employee!" << std::endl;
                // Call employee-specific functions here
                int choice{}, age{};
                std::string accountNumber{}, email{}, firstname{}, lastname{}, password{};

                while(1) {

                    std::cout << "Menu Options" << std::endl
                        << "1 - Print all customers" << std::endl
                        << "2 - Create new customer" << std::endl
                        << "3 - Delete customer" << std::endl
                        << "4 - Log out" << std::endl
                        << "Choose: ";
                    std::cin >> choice;

                    if(choice == 4) {
                        std::cout << "Logging out..." << std::endl;
                        break;
                    }

                    switch (choice) {
                        case 1:
                            employeeOperations.printAllCustomerAccounts();
                            break;
                        case 2:
                            std::cout << "=====CREATE NEW CUSTOMER=====" << std::endl;

                            std::cout << "Enter account number: ";
                            std::cin >> accountNumber;

                            std::cout << "Enter email address: ";
                            std::cin >> email;

                            std::cout << "Enter age: ";
                            std::cin >> age;

                            std::cout << "Enter firstname: ";
                            std::cin >> firstname;

                            std::cout << "Enter lastname: ";
                            std::cin >> lastname;

                            std::cout << "Enter password: ";
                            std::cin >> password;

                            employeeOperations.createNewCustomer(accountNumber, email, age, firstname, lastname, password);
                            break;
                        case 3:
                            // Delete a customer
                            break;

                    }
                }

            } else {
                std::cout << "Login failed: Try again!" << std::endl;
            }
        }
    } else {
        logger.log(LogLevel::ERROR, "Failed to connect to the database!");
        //std::cout << "Failed to connect to the database!" << std::endl;
    }
    return 0;
}