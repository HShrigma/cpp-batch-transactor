#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <format>
#include <regex>

class TransactionProcessor
{
private:
    // Validates Arguments provided to the process transaction function
    static bool validateArgs(std::vector<std::string> *args);
    // Helper function to print type errors
    static void printInvalidTypeMsg(u_int index, std::string expected, std::string received);
    // Helper function for case insenstivie string comparison
    static bool compareStringsInsensitive(std::string &str1, std::string &str2);
    // Helper function for timestamp validation
    static bool isValidISOTimestamp(const std::string& timestamp);
public:
    /*Takes in Vector String in Format:
        user_id: int

        type: string – "credit" or "debit"

        amount: float

        timestamp: ISO 8601 string (optional, could use current time if missing)
    */
    static void processTransaction(std::vector<std::string> args);
    static std::string getISOCurrentTimeStamp();
};