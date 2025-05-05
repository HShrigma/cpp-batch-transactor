#include "transaction.h"

Transaction Transaction::fromVector(const std::vector<std::string> &fields){
    Transaction t;
    t.user_id = std::stoul(fields.at(0));
    t.type = fields.at(1);
    t.amount = std::stof(fields.at(2));
    t.timestamp = fields.at(3);
    return t;
}