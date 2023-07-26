#include <iostream>
#include <mysql.h>

// Inclusion of header files
#include "Employee_Files/EmployeeAccount.h"
#include "Customer_Files/CustomerOperations.h"

int main() {

    std::unique_ptr<CustomerOperations> customer = std::make_unique<CustomerOperations>("localhost", "root", "Sebastian2001Brinch6443", "bank_management_system_db");

    std::cout << "Enter a customer id: ";
    int customer_id{};
    std::cin >> customer_id;

    /*
    std::cout << "Enter amount to withdraw: ";
    double amount{};
    std::cin >> amount;
    */

    //customer->deposit(customer_id, amount);
    customer->showAccountDetails(customer_id);
    return 0;
}

