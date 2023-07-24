//
// Created by Sebastian Brinch on 23/07/2023.
//
#include <regex>

#include "CustomerAccount.h"

CustomerAccount::CustomerAccount(int cust_id, int usr_id, std::string acc_num, int bal_cents,
                                 std::string eml, int age_val, std::string fname, std::string lname)
    :customer_id(cust_id) ,user_id(usr_id), account_number(acc_num), balance_cents(bal_cents),
    email(eml), age(age_val), firstname(fname), lastname(lname){

}
// Getter and setter for customer ID
int CustomerAccount::getCustomerId() const {
    return customer_id;
}

// Getter and setter for user ID
int CustomerAccount::getUserId() const {
    return user_id;
}

void CustomerAccount::setUserId(int usr_id) {
    if (usr_id >= 0) {
        user_id = usr_id;
    } else {
        throw std::invalid_argument("Invalid customer ID. Must be a positive number.");
    }
}

// Getter and setter for account number
std::string CustomerAccount::getAccountNumber() const {
    return account_number;
}

void CustomerAccount::setAccountNumber(std::string acc_num) {
    if (acc_num.length() != 20) {
        throw std::invalid_argument("Invalid account number. Must be 20 characters.");
    } else {
        account_number = acc_num;
    }
}

// Getter and setter for balance
int CustomerAccount::getBalanceCents() const {
    return balance_cents;
}

void CustomerAccount::setBalanceCents(int bal_cents) {
    balance_cents = bal_cents;
}

// Getter and setter for email
std::string CustomerAccount::getEmail() const {
    return email;
}

void CustomerAccount::setEmail(std::string eml) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    if(std::regex_match(eml, pattern)) {
        email = eml;
    } else {
        throw std::invalid_argument("Invalid email: Must be with in the requirements.");
    }
}

// Getter and setter for age
int CustomerAccount::getAge() const {
    return age;
}

void CustomerAccount::setAge(int age_val) {
    if (age_val < 99) {
        age = age_val;
    } else {
        throw std::invalid_argument("Invalid age: Age must be under 99.");
    }
}

// Getter and setter for firstname
std::string CustomerAccount::getFirstName() const {
    return firstname;
}

void CustomerAccount::setFirstName(std::string fname) {
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

// Getter and setter for lastname
std::string CustomerAccount::getLastName() const {
    return lastname;
}

void CustomerAccount::setLastName(std::string lname) {
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

// Destructor for customer account
CustomerAccount::~CustomerAccount() = default;