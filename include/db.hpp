#ifndef DB_HPP
#define DB_HPP

#include <pqxx/pqxx>  // libpqxx for PostgreSQL
#include <iostream>

class Database {
public:
    static pqxx::connection connectToDB() {
        try {
            // Update with the correct connection string
            pqxx::connection conn("dbname=batch_db user=batch_user password=batch_pass host=localhost port=5432");
            if (conn.is_open()) {
                std::cout << "Connected to the database!" << std::endl;
                return conn;
            } else {
                std::cerr << "Failed to connect to the database!" << std::endl;
                exit(1);  // Exit if connection fails
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }
    }
};

#endif