#include <iostream>
#include "transaction/transaction_processor.h"
#include "transaction/helpers/transaction_validator.h"
#include "io/csv_reader.h"

const std::string CSV_PATH = "../data/transactions.csv";
void testProcessingValidation()
{
    std::vector<std::string> invalid_size{"test", "test3"};
    std::vector<std::string> invalid_types{"-20", "test1", "test2"};

    std::string stampISO{TransactionValidator::getISOCurrentTimeStamp()};

    std::vector<std::string> valid{"20", "credit", "59.99", stampISO};
    std::vector<std::string> valid_no_timestamp{"20", "credit", "59.99"};

    TransactionProcessor::processTransaction(invalid_size);
    TransactionProcessor::processTransaction(invalid_types);
    TransactionProcessor::processTransaction(valid);
    TransactionProcessor::processTransaction(valid_no_timestamp);
}

int main(int argc, char const *argv[])
{
    CSVReader reader = CSVReader(CSV_PATH);
    auto parsed = reader.readAll();
    for (auto row : parsed)
    {
        std::cout << "ROW:" << std::endl;
        std::cout << "user_id: " << row.at(0) << std::endl;
        std::cout << "type: " << row.at(1) << std::endl;
        std::cout << "amount: " << row.at(2) << std::endl;
        std::cout << "timestamp: " << (row.size() > 3 ? row.at(3) : "none") << std::endl;
    }
    return 0;
}