//
// Created by Sebastian Brinch on 23/07/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H
#define BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H

#include <string>

class EmployeeAccount {
public:
    static const int MAX_LENGTH = 30;
    EmployeeAccount(int = 0, std::string = "", std::string = "");
    ~EmployeeAccount();

    void setEmployeeId(int);
    void setFirstName(std::string);
    void setLastName(std::string);

    int getEmployeeId() const;
    std::string getFirstName() const;
    std::string getLastName() const;

private:
    int employeeId{};
    char firstname[MAX_LENGTH]{};
    char lastname[MAX_LENGTH]{};
};


#endif //BANKMANAGEMENTSYSTEM_EMPLOYEEACCOUNT_H
