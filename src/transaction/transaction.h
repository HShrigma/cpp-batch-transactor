#pragma once
#include <string>
#include <vector>

struct Transaction {
    unsigned long user_id;
    std::string type;         // "credit" or "debit"
    float amount;
    std::string timestamp;    // ISO 8601 UTC

    static Transaction fromVector(const std::vector<std::string>* fields);
};