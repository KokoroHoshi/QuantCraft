#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>

#include <nlohmann/json.hpp>

#include "../core/Candlestick.h"

using json = nlohmann::json;

namespace Parser {
    std::vector<Candlestick> parseTWSEJsonArray(const json& data);
    std::vector<Candlestick> parseTWSEJsonFile(const std::string& filepath);

    std::vector<Candlestick> parseYfinanceJson(const json& data);
    std::vector<Candlestick> parseYfinanceJsonFile(const std::string& filepath);
}

#endif // JSONPARSER_H