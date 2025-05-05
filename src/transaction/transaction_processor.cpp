#include "transaction_processor.h"

void TransactionProcessor::processTransaction(std::vector<std::string> args)
{
    std::cout << "[LOG] process_transaction called!" << std::endl;
    if (validateArgs(&args))
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
bool TransactionProcessor::validateArgs(std::vector<std::string> *args)
{
    // Validate Length
    if (args->size() < 3 || args->size() > 4)
    {
        std::cout << "[ERROR] TransactionProcessor::validateArgs: Invalid Arguments Size Error!"
                  << std::endl
                  << "Size cannot be: " << args->size() << std::endl;
        return false;
    }

    bool valid = true;
    // validate user_ID type
    try
    {
        u_long id{std::stoul(args->at(0))};
    }
    catch (const std::exception &e)
    {
        printInvalidTypeMsg(0, "Unsigned Long convertible value", args->at(0));
        valid = false;
    }

    // validate Credit or Debit
    std::vector<std::string> allowedTypes{"credit", "debit"};

    bool isTypeValid{false};
    for (auto &i : allowedTypes)
    {
        if (compareStringsInsensitive(args->at(1), i))
        {
            isTypeValid = true;
            break;
        }
    }
    valid = isTypeValid;
    if (!valid)
    {
        printInvalidTypeMsg(1, "\"Credit\" or \"Debit\" (case insensitive)", args->at(1));
    }

    // validate amount type
    try
    {
        float id{std::stof(args->at(2))};
    }
    catch (const std::exception &e)
    {
        printInvalidTypeMsg(2, "Floating point convertible numeric value", args->at(2));
        valid = false;
    }

    // Check for existing timestamp and switch to current if none is present or invalid
    if (args->size() == 3)
    {
        args->emplace_back(getISOCurrentTimeStamp());
    }
    else if (!isValidISOTimestamp(args->at(3)))
    {
        args->at(3) = getISOCurrentTimeStamp();
    }

    return valid;
}

void TransactionProcessor::printInvalidTypeMsg(u_int index, std::string expected, std::string received)
{
    std::cout << "[ERROR] TransactionProcessor::validateArgs: Argument Type Error at index " << index << ':' << std::endl
              << "Expected: " << expected << std::endl
              << "Received: " << received << std::endl;
}

bool TransactionProcessor::compareStringsInsensitive(std::string &str1, std::string &str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }

    return true;
}
std::string TransactionProcessor::getISOCurrentTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    return std::format("{:%Y-%m-%dT%H:%M:%SZ}", now);
}
bool TransactionProcessor::isValidISOTimestamp(const std::string &timestamp)
{
    // Regex for ISO 8601 (UTC): YYYY-MM-DDTHH:MM:SSZ
    const std::regex isoRegex(
        R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z$)");

    return std::regex_match(timestamp, isoRegex);
}