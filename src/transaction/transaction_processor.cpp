#include "transaction_processor.h"

void TransactionProcessor::processTransaction(std::vector<std::string> args)
{
    std::cout << "[LOG] process_transaction called!" << std::endl;
    if (TransactionValidator::areArgsValid(&args))
    {
        std::cout << "[SUCCESS] Argument types are valid!" << std::endl;

        for (auto &&i : args)
        {
            std::cout << i << " | ";
        }
        std::cout << std::endl;
        return;
    }
    std::cout << "[ERROR] process_transaction called: Invalid Arguments" << std::endl;
}