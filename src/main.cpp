#include <iostream>
#include "transaction/transaction_processor.h"
#include "transaction/helpers/transaction_validator.h"
#include "io/csv_reader.h"
#include "db.hpp"

const std::string CSV_PATH = "../data/transactions.csv";

void processTransactions(const std::vector<std::vector<std::string>> &transactions)
{
    pqxx::connection conn{Database::connectToDB()};
    pqxx::work txn(conn);
    bool success{true};
    std::string query;

    for (const auto &row : transactions)
    {
        query = TransactionProcessor::buildQuery(
            TransactionProcessor::buildTransaction(row, true)); // delete ', true' if not debugging
        try
        {
            if (query != "[INVALID]")
            {
                txn.exec(query);
                std::cout << "[INFO] Query Executed:" << query << std::endl;
            }
            else{
                std::cout << "[WARNING] Query Invalid, will not execute." << query << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "[ERROR] an error ocurred while executing query: " << query << std::endl;
            std::cerr << e.what() << '\n';
            success = false;
            continue;
        }
    }
    if (success)
    {
        txn.commit();
        std::cout << "[INFO] Transactions successfully committed to the database!" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    CSVReader reader = CSVReader(CSV_PATH);
    auto transactions = reader.readAll();
    processTransactions(transactions);
    return 0;
}