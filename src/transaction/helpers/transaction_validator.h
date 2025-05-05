#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <format>
#include <regex>

class TransactionValidator
{
private:
    static bool isValidSize(std::vector<std::string> *args)
    {
        if (args->size() >= 3 && args->size() <= 4)
            return true;

        std::cout << "[ERROR] TransactionProcessor::validateArgs: Invalid Arguments Size Error!"
                  << std::endl
                  << "Size cannot be: " << args->size() << std::endl;
        return false;
    }
    static bool canParseToULong(std::vector<std::string> *args, int index)
    {
        try
        {
            u_long id{std::stoul(args->at(index))};
            return true;
        }
        catch (const std::exception &e)
        {
            printInvalidTypeMsg(index, "Unsigned Long convertible value", args->at(index));
            return false;
        }
    }
    static bool canParseTofloat(std::vector<std::string> *args, int index)
    {
        try
        {
            float amount{std::stof(args->at(index))};
            return true;
        }
        catch (const std::exception &e)
        {
            printInvalidTypeMsg(index, "Floating point convertible numeric value", args->at(index));
            return false;
        }
    }
    static bool isValidTypeString(std::vector<std::string> *args, int index)
    {
        // validate Credit or Debit
        std::vector<std::string> allowedTypes{"credit", "debit"};

        bool valid{false};
        for (auto &i : allowedTypes)
        {
            if (compareStringsInsensitive(args->at(index), i))
            {
                valid = true;
                break;
            }
        }
        if (!valid)
        {
            printInvalidTypeMsg(index, "\"Credit\" or \"Debit\" (case insensitive)", args->at(index));
        }

        return valid;
    }

    static void validateTimeStamp(std::vector<std::string> *args, int index)
    {
        // Check for existing timestamp and switch to current if none is present or invalid
        if (args->size() == index)
        {
            args->emplace_back(getISOCurrentTimeStamp());
        }
        else if (!isValidISOTimestamp(args->at(index)))
        {
            args->at(index) = getISOCurrentTimeStamp();
        }
    }

    static void printInvalidTypeMsg(u_int index, std::string expected, std::string received)
    {
        std::cout << "[ERROR] TransactionValidator::validateArgs: Argument Type Error at index " << index << ':' << std::endl
                  << "Expected: " << expected << std::endl
                  << "Received: " << received << std::endl;
    }

public:
    static bool compareStringsInsensitive(std::string &str1, std::string &str2)
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
    static std::string getISOCurrentTimeStamp()
    {
        auto now = std::chrono::system_clock::now();
        return std::format("{:%Y-%m-%dT%H:%M:%SZ}", now);
    }
    static bool isValidISOTimestamp(const std::string &timestamp)
    {
        // Regex for ISO 8601 (UTC): YYYY-MM-DDTHH:MM:SSZ
        const std::regex isoRegex(
            R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z$)");

        return std::regex_match(timestamp, isoRegex);
    }
    static bool areArgsValid(std::vector<std::string> *args)
    {
        // Validate Length
        if (TransactionValidator::isValidSize(args))
        {
            bool valid = TransactionValidator::canParseToULong(args, 0);
            valid = TransactionValidator::isValidTypeString(args, 1);
            valid = TransactionValidator::canParseTofloat(args, 2);
            TransactionValidator::validateTimeStamp(args, 3);

            return valid;
        }
        return false;
    }
};
