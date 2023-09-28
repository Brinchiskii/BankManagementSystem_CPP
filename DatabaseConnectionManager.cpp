//
// Created by Sebastian Brinch on 01/08/2023.
//
#include "DatabaseConnectionManager.h"
#include "Logging/Logger.h"
#include <iostream>
#include <string>

#include "Logging/Logger.h"

Logger logger("/Users/sebastianbrinch/CLionProjects/BankManagementSystem/Logging/Logs/logfile.txt");

DatabaseConnectionManager::DatabaseConnectionManager() : db_conn(nullptr, &mysql_close) {}

DatabaseConnectionManager::~DatabaseConnectionManager() {
    // The smart pointer will automatically handle deallocation, no need to call disconnect here.
}

bool DatabaseConnectionManager::connect(const std::string &host, const std::string &user, const std::string &password,
                                        const std::string &database) {
    disconnect();

    db_conn.reset(mysql_init(nullptr));
    if (!db_conn) {
        std::cout << "Failed to initialize MySQL connection!" << std::endl;
        return false;
    }

    if (!mysql_real_connect(db_conn.get(), host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, nullptr, 0)) {
        logger.log(LogLevel::ERROR, "Failed to connect to the database: " + std::string(mysql_error(db_conn.get())));
        //std::cout << "Failed to connect to the database: " << mysql_error(db_conn.get()) << std::endl;
        return false;
    }

    logger.log(LogLevel::INFO, "Connected to the database successfully: " + database);
    //std::cout << "Connected to the database successfully!" << std::endl;

    return true;
}

bool DatabaseConnectionManager::disconnect() {
    if (db_conn) {
        mysql_close(db_conn.get());
        db_conn.reset();
    }
    return true;
}

MYSQL* DatabaseConnectionManager::getConnection() const {
    return db_conn.get();
}