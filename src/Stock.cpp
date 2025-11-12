#include "Stock.h"

#include <sstream>
#include <iostream>

#include <stdexcept>

Stock::Stock(const std::string& symbol_,
            const std::string& date_,
            double open_,
            double high_,
            double low_,
            double close_,
            long long volume_
            ) : symbol(symbol_),
                date(date_),
                open(open_),
                high(high_),
                low(low_),
                close(close_),
                volume(volume_) {}

// private
long long Stock::parseVolume(const std::string& str) {
    std::string clean;
    for (char c : str) if (isdigit(c)) clean += c;
    return std::stoll(clean);
}

// public
void Stock::print() const {
    std::cout << symbol << " " << date << " O:" << open << " H:" << high << " L:" << low << " C:" << close << " V:" << volume << std::endl;
}

Stock Stock::fromJsonRow(const std::string& symbol, const std::vector<std::string>& row) {
    // row[0]: date in ROC year YYY-DD-MM
    std::string date_str = row[0];
    int roc_year, month, day;

    try {
        size_t pos1 = date_str.find('/');
        size_t pos2 = date_str.rfind('/');

        if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 == pos2) {
            throw std::runtime_error("Invalid date format: " + date_str);
        }

        roc_year = std::stoi(date_str.substr(0, pos1));
        month = std::stoi(date_str.substr(pos1 + 1, pos2 - pos1 -1));
        day = std::stoi(date_str.substr(pos2 + 1));
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse date: " + date_str);
    }

    int year = roc_year + 1911;

    std::ostringstream oss;
    oss << year << "-"
        << (month < 10 ? "0" : "") << month << "-"
        << (day < 10 ? "0" : "") << day;
    std::string formatted_year = oss.str();

    double open = std::stod(row[3]);
    double high = std::stod(row[4]);
    double low  = std::stod(row[5]);
    double close = std::stod(row[6]);
    long long volume = parseVolume(row[1]);

    return Stock(symbol, formatted_year, open, high, low, close, volume);
}