//
// Created by Sebastian Brinch on 23/07/2023.
//
#include <regex>

#include "EmployeeAccount.h"

// constructor for EmployeeAccount()
EmployeeAccount::EmployeeAccount(int empl_id, int usr_id, std::string eml, std::string fname, std::string lname)
    :employeeId(empl_id), user_id(usr_id), email(eml), firstname(fname), lastname(lname) {

}

// Getter for employee id
int EmployeeAccount::getEmployeeId() const {
    return employeeId;
}

// Getter and setter for user id
int EmployeeAccount::getUserId() const {
    return user_id;
}

void EmployeeAccount::settUserId(int usr_id) {
    if(usr_id >= 0) {
        user_id = usr_id;
    } else {
        throw std::invalid_argument("Invalid user id. Must be a positive number.");
    }
}

// Getter and setter for email
std::string EmployeeAccount::getEmail() const {
    return email;
}

void EmployeeAccount::setEmail(std::string eml) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    if(std::regex_match(eml, pattern)) {
        email = eml;
    } else {
        throw std::invalid_argument("Invalid email: Must be with in the requirements.");
    }
}

// Getter and setter for first name
std::string EmployeeAccount::getFirstName() const {
    return firstname;
}

void EmployeeAccount::setFirstName(std::string fname) {
    if (fname.empty()) {
        throw std::invalid_argument("Invalid: firstname cannot be empty.");
        return;
    }

    if (!isAlpha(fname)) {
        throw std::invalid_argument("Invalid: First name must contain only alphabetic characters");
        return;
    }

    if (fname.length() > maxNameLength) {
        throw std::invalid_argument("Invalid: First name is too long, Maximum length is 50");
        return;
    }

    firstname = fname;
}
// Getter and setter for last name
std::string EmployeeAccount::getLastName() const {
    return lastname;
}

void EmployeeAccount::setLastName(std::string lname) {
    if (lname.empty()) {
        throw std::invalid_argument("Invalid: lastname cannot be empty.");
        return;
    }

    if(!isAlpha(lname)) {
        throw std::invalid_argument("Invalid: Last name must contain only alphabetic characters");
        return;
    }

    if(lname.length() > maxNameLength) {
        throw std::invalid_argument("Invalid: Last name is too long, Maximum length is 50");
        return;
    }

    lastname = lname;
}

// destructor for EmployeeAccount()
EmployeeAccount::~EmployeeAccount() = default;