//
// Created by Sebastian Brinch on 01/08/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_DATABASECONNECTIONMANAGER_H
#define BANKMANAGEMENTSYSTEM_DATABASECONNECTIONMANAGER_H

#include <mysql.h>
#include <memory>
#include <string>

class DatabaseConnectionManager {
public:
    DatabaseConnectionManager();
    ~DatabaseConnectionManager();

    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    bool disconnect();

    MYSQL* getConnection() const;

private:
    std::unique_ptr<MYSQL, decltype(&mysql_close)> db_conn;
};

#endif // BANKMANAGEMENTSYSTEM_DATABASECONNECTIONMANAGER_H
