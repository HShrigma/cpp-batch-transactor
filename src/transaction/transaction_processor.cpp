#include "transaction_processor.h"

Transaction *TransactionProcessor::buildTransaction(std::vector<std::string> args, bool debug)
{
  std::cout << "[INFO] processTransaction called." << std::endl;
  if (TransactionValidator::areArgsValid(&args))
  {
    std::cout << "[INFO] Argument are valid. Returning transaction object." << std::endl;
    Transaction *t = new Transaction(args);
    if (debug)
    {
      std::cout << "[INFO] Transaction created:" << std::endl
                << "User ID: " << t->user_id << std::endl
                << "Type: " << t->type << std::endl
                << "Amount: " << t->amount << "\n"
                << "Timestamp: " << t->timestamp << "\n";
    }

    return t;
  }
  std::cout << "[ERROR] process_transaction called: Invalid Arguments" << std::endl;
  return nullptr;
}

std::string TransactionProcessor::buildQuery(Transaction *t)
{
  if (t != nullptr)
  {
    std::string res = "INSERT INTO transactions (user_id, transaction_type, amount, timestamp) VALUES(";
    res+= std::to_string(t->user_id) + 
    ", '" + t->type + "', " + 
    std::to_string(t->amount) +
    ", '" + t->timestamp + "');";

    return res;
  }
  return "[INVALID]";
}
