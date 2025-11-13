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

    std::string unixToDateString(long timestamp) {
        std::time_t t = static_cast<time_t>(timestamp);
        std::tm tm{};
        localtime_r(&t, &tm);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        return oss.str();
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

    std::vector<Candlestick> parseYfinanceJson(const json& data) {
        std::vector<Candlestick> candles;

        try {
            if (!data.contains("chart"))
                throw std::runtime_error("Missing 'chart' field");
            if (data["chart"]["error"] != nullptr)
                throw std::runtime_error("YFinance returned an error");

            auto result = data["chart"]["result"].at(0);
            const auto& timestamps = result["timestamp"];
            const auto& quote = result["indicators"]["quote"].at(0);

            size_t n = timestamps.size();

            if (n == 0) throw std::runtime_error("No candle data found");

            candles.reserve(n);

            for (size_t i = 0; i < n; i++) {
                std::string date = unixToDateString(timestamps[i].get<long>());
            
                double open   = quote["open"][i].get<double>();
                double high   = quote["high"][i].get<double>();
                double low    = quote["low"][i].get<double>();
                double close  = quote["close"][i].get<double>();
                long long vol = quote["volume"][i].get<long long>();

                candles.emplace_back(date, open, high, low, close, vol);
            }
        } catch (const std::exception& e) {
            std::cerr << "[parseYfinanceJson] Error: " << e.what() << "\n";
            throw;
        }

        return candles;
    }

    std::vector<Candlestick> parseYfinanceJsonFile(const std::string& filepath) {
        std::ifstream fin(filepath);
        if (!fin) throw std::runtime_error("Failed to open file: " + filepath);

        json data;
        fin >> data;
        fin.close();

        return parseYfinanceJson(data);
    }
}
