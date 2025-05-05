#pragma once
#include "helpers/transaction_validator.h"
#include "transaction.h"

class TransactionProcessor
{
private:
public:
    /*Takes in Vector String in Format:
        user_id: int

        type: string – "credit" or "debit"

        amount: float

        timestamp: ISO 8601 string (optional, could use current time if missing)
    */
    static void processTransaction(std::vector<std::string> args);
};