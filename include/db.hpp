#ifndef DB_HPP
#define DB_HPP

#include <pqxx/pqxx> // libpqxx for PostgreSQL
#include <iostream>

class Database
{
public:
    static pqxx::connection connectToDB()
    {
        try
        {

            const char *db_name = std::getenv("DB_NAME");
            const char *db_user = std::getenv("DB_USER");
            const char *db_password = std::getenv("DB_PASSWORD");
            const char *db_host = std::getenv("DB_HOST");
            const char *db_port = std::getenv("DB_PORT");

            if (!db_name || !db_user || !db_password || !db_host || !db_port)
            {
                std::cerr << "[Error] Missing database credentials in environment variables." << std::endl;
                exit(1); // Exit if connection fails
            }
            std::string conn_str = "dbname=" + std::string(db_name) +
                                   " user=" + std::string(db_user) +
                                   " password=" + std::string(db_password) +
                                   " host=" + std::string(db_host) +
                                   " port=" + std::string(db_port);
            pqxx::connection conn(conn_str);
            
            if (conn.is_open())
            {
                std::cout << "Connected to the database!" << std::endl;
                return conn;
            }
            else
            {
                std::cerr << "Failed to connect to the database!" << std::endl;
                exit(1); // Exit if connection fails
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }
    }
};

#endif