#ifndef STOCKSERVICE_H
#define STOCKSERVICE_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class StockService {
public:
    static json fetchStock(
        const std::string& symbol,
        const std::string& range = "1y",
        const std::string& interval = "1d"
    );
};

#endif