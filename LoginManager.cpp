//
// Created by Sebastian Brinch on 01/08/2023.
//
#include "LoginManager.h"

LoginManager::LoginManager(DatabaseConnectionManager &dbManager) : dbManager(dbManager) {}

LoginManager::UserRole LoginManager::login(const std::string &username, const std::string &password, LoginManager::UserRole &role) {
    MYSQL* dbConnection = dbManager.getConnection();

    std::string sql = "SELECT role FROM users WHERE username='" + username + "' AND password='" + password + "'";

    if (!mysql_query(dbConnection, sql.c_str())) {
        MYSQL_RES *result = mysql_store_result(dbConnection);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row) {
                std::string roleStr = row[0];
                mysql_free_result(result);

                if (roleStr == "Customer") {
                    role = UserRole::Customer;
                    return UserRole::Customer;
                } else if (roleStr == "Employee") {
                    role = UserRole::Employee;
                    return UserRole::Employee;
                }
            }
        }
    }

    role = UserRole::Unknown;
    return UserRole::Unknown;
}