//
// Created by Sebastian Brinch on 23/07/2023.
//

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

void CustomerAccount::setCustomerId(int cust_id) {
    if (cust_id >= 0) {
        customer_id = cust_id;
    } else {
        throw std::invalid_argument("Invalid customer ID. Must be a positive integer.");
    }
}

// Getter and setter for user ID

// Getter and setter for account number

// Getter and setter for balance

// Getter and setter for email

// Getter and setter for age

// Getter and setter for firstname

// Getter and setter for lastname

// Destructor for customer account
CustomerAccount::~CustomerAccount() = default;