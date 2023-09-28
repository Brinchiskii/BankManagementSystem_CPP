//
// Created by Sebastian Brinch on 01/08/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_LOGINMANAGER_H
#define BANKMANAGEMENTSYSTEM_LOGINMANAGER_H

#include <string>
#include "DatabaseConnectionManager.h"

class LoginManager {
public:
    enum class UserRole {
        Customer,
        Employee,
        Unknown
    };

    LoginManager(DatabaseConnectionManager& dbManager);

    LoginManager::UserRole login(const std::string& username, const std::string& password, UserRole& role);

private:
    DatabaseConnectionManager& dbManager;
};

#endif // BANKMANAGEMENTSYSTEM_LOGINMANAGER_H
