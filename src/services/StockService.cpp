#include "StockService.h"

#include <stdexcept>

#include <nlohmann/json.hpp>
#include <httplib.h>

json StockService::fetchStock(const std::string& symbol, const std::string& range, const std::string& interval) {
    std::string root_url = "query1.finance.yahoo.com";
    std::string api = "/v8/finance/chart/" + symbol + "?range=" + range + "&interval=" + interval;

    httplib::SSLClient cli(root_url);
    auto res = cli.Get(api.c_str());
    
    if (!res) throw std::runtime_error("Connection failed");

    if(res->status != 200) throw std::runtime_error("HTTP status" + std::to_string(res->status));

    return json::parse(res->body);
}