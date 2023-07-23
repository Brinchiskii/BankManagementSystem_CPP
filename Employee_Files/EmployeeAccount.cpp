//
// Created by Sebastian Brinch on 23/07/2023.
//

#include "EmployeeAccount.h"

// constructor for EmployeeAccount()
EmployeeAccount::EmployeeAccount(int acno, std::string fname, std::string lname) {
    setEmployeeId(acno);
    setFirstName(fname);
    setLastName(lname);
}

void EmployeeAccount::setEmployeeId(int employee_Id) {
    employeeId = employee_Id;
}

void EmployeeAccount::setFirstName(std::string first_name) {
    const char* fn = first_name.data();
    int len = first_name.size();
    len = (len < MAX_LENGTH ? len : MAX_LENGTH - 1);
    strncpy(firstname, fn, len);
    firstname[len] = '\0';
}

void EmployeeAccount::setLastName(std::string last_name) {
    const char* ln = last_name.data();
    int len = last_name.size();
    len = (len < MAX_LENGTH ? len : MAX_LENGTH - 1);
    strncpy(lastname, ln, len);
    lastname[len] = '\0';
}

int EmployeeAccount::getEmployeeId() const {
    return employeeId;
}

std::string EmployeeAccount::getFirstName() const {
    return firstname;
}

std::string EmployeeAccount::getLastName() const {
    return lastname;
}

// destructor for EmployeeAccount()
EmployeeAccount::~EmployeeAccount() = default;