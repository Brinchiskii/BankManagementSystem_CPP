//
// Created by Sebastian Brinch on 23/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_CUSTOMERACCOUNT_H
#define BANKMANAGEMENTSYSTEM_CUSTOMERACCOUNT_H

#include <string>

class CustomerAccount {
public:
    static const int maxNameLength = 50;
    static const int MAX_AGE_SIZE = 99;

    // Constructor with default arguments
    CustomerAccount(int cust_id = 0, int usr_id = 0, std::string acc_num = "", int bal_cents = 0,
                    std::string eml = "", int age_val = MAX_AGE_SIZE, std::string fname = "", std::string lname = "");

    //~CustomerAccount();

    int getCustomerId() const;
    int getUserId() const;
    std::string getAccountNumber() const;
    int getBalanceCents() const;
    std::string getEmail() const;
    int getAge() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    double getBalanceInDollars() const;

    void setCustomerId(int);
    void setUserId(int);
    void setAccountNumber(std::string);
    void setBalanceCents(int);
    void setEmail(std::string);
    void setAge(int);
    void setFirstName(std::string);
    void setLastName(std::string);

private:
    int customer_id{};
    int user_id{};
    std::string account_number;
    int balance_cents{};
    std::string email;
    int age{MAX_AGE_SIZE};
    std::string firstname;
    std::string lastname;

    // Function to check if string contains only alphabetic characters.
    bool isAlpha(const std::string& str) {
        for (char c : str) {
            if (!std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }
};

#endif //BANKMANAGEMENTSYSTEM_CUSTOMERACCOUNT_H
