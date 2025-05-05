#include "transaction.h"

Transaction::Transaction(const std::vector<std::string> &fields){
    user_id = std::stoul(fields.at(0));
    type = fields.at(1);
    amount = std::stof(fields.at(2));
    timestamp = fields.at(3);
}