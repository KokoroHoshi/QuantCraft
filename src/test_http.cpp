#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    httplib::SSLClient cli("www.twse.com.tw");
    std::string path = "/rwd/zh/afterTrading/STOCK_DAY?date=20251111&stockNo=0050&response=json";
    auto res = cli.Get(path.c_str());
    
    if (!res) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    if (res->status != 200) {
        std::cerr << "HTTP status: " << res->status << "\n";
        return 1;
    }

    json data = json::parse(res->body);
    if (data["stat"] != "OK") {
        std::cerr << "Invalid response from TWSE\n";
        return 1;
    }

    std::cout << "股票：" << data["title"] << "\n";
    std::cout << "日期\t\t收盤價\n";

    for (auto &row : data["data"]) {
        std::string date = row[0];
        std::string close = row[6];
        std::cout << date << "\t" << close << "\n";
    }

    return 0;
}