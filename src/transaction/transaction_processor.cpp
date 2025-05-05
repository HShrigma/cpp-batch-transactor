#include "transaction_processor.h"

void TransactionProcessor::processTransaction(std::vector<std::string> args)
{
    std::cout << "[INFO] processTransaction called." << std::endl;
    if (TransactionValidator::areArgsValid(&args))
    {
        std::cout << "[INFO] Argument are valid." << std::endl;
        Transaction t = Transaction::fromVector(args);
        std::cout << "[INFO] Transaction created:"<< std::endl
          << "User ID: " << t.user_id << std::endl
          << "Type: " << t.type << std::endl
          << "Amount: " << t.amount << "\n"
          << "Timestamp: " << t.timestamp << "\n";
        
        return;
    }
    std::cout << "[ERROR] process_transaction called: Invalid Arguments" << std::endl;
}