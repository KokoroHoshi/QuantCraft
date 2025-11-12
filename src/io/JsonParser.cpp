#include "JsonParser.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <stdexcept>

using json = nlohmann::json;

namespace {
    long long parseVolume(const std::string& str) {
        std::string clean;
        for (char c : str) if (isdigit(c)) clean += c;
        return std::stoll(clean);
    }

    std::string parseROCDate(const std::string& date_str) {
        // ROC_Y/MM/DD => YYYY-MM-DD
        try {
            size_t pos1 = date_str.find('/');
            size_t pos2 = date_str.rfind('/');

            if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 == pos2) {
                throw std::runtime_error("Invalid date format: " + date_str);
            }

            int roc_year = std::stoi(date_str.substr(0, pos1));
            int month = std::stoi(date_str.substr(pos1 + 1, pos2 - pos1 -1));
            int day = std::stoi(date_str.substr(pos2 + 1));

            int year = roc_year + 1911;

            std::ostringstream oss;
            oss << year << "-"
                << (month < 10 ? "0" : "") << month << "-"
                << (day < 10 ? "0" : "") << day;
            
            return oss.str();
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to parse date: " + date_str);
        }
    }
}

namespace Parser {
    std::vector<Candlestick> parseTWSEJsonArray(const json& data) {
        std::vector<Candlestick> candles;

        for (const auto& row : data) {
            try {
                std::string date = parseROCDate(row[0].get<std::string>());
                double open = std::stod(row[3].get<std::string>());
                double high = std::stod(row[4].get<std::string>());
                double low  = std::stod(row[5].get<std::string>());
                double close= std::stod(row[6].get<std::string>());
                long long volume = parseVolume(row[1].get<std::string>());

                candles.emplace_back(date, open, high, low, close, volume);
            } catch (const std::exception& e) {
                std::cerr << "Failed to parse row: " << row.dump() << "\n";
                std::cerr << "Error: " << e.what() << "\n";
                throw;
            }
        }

        return candles;
    }

    std::vector<Candlestick> parseTWSEJsonFile(const std::string& filepath) {
        std::ifstream fin(filepath);
        if (!fin) throw std::runtime_error("Failed to open file: " + filepath);

        json data;
        fin >> data;
        fin.close();

        return parseTWSEJsonArray(data);
    }
}
