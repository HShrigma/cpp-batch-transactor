#include <iostream>
#include "transaction/transaction_processor.h"
#include "transaction/helpers/transaction_validator.h"
int main(int argc, char const *argv[])
{
    std::vector<std::string> invalid_size{"test", "test3"};
    std::vector<std::string> invalid_types{"-20", "test1", "test2"};

    std::string stampISO {TransactionValidator::getISOCurrentTimeStamp()};

    std::vector<std::string> valid{"20", "credit", "59.99", stampISO};
    std::vector<std::string> valid_no_timestamp{"20", "credit", "59.99"};

    TransactionProcessor::processTransaction(invalid_size);
    TransactionProcessor::processTransaction(invalid_types);
    TransactionProcessor::processTransaction(valid);
    TransactionProcessor::processTransaction(valid_no_timestamp);
    return 0;
}