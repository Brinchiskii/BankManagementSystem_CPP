//
// Created by Sebastian Brinch on 23/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H
#define BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H

#include <string>

class EmployeeAccount {
public:
    static const int maxNameLength = 30;
    EmployeeAccount(int empl_id = 0, int usr_id = 0, std::string eml = "", std::string fname = "", std::string lname = "");
    ~EmployeeAccount();

    int getEmployeeId() const;
    int getUserId() const;
    std::string getEmail() const;
    std::string getFirstName() const;
    std::string getLastName() const;

    void settUserId(int);
    void setEmail(std::string);
    void setFirstName(std::string);
    void setLastName(std::string);

private:
    int employeeId{};
    int user_id{};
    std::string email;
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


#endif //BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H
