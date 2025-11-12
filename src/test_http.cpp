#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // get today date
    std::time_t t = std::time(nullptr);
    std::tm tm_obj;
    localtime_r(&t, &tm_obj);

    char buffer[9]; // YYYYMMDD
    std::strftime(buffer, sizeof(buffer), "%Y%m%d", &tm_obj);
    std::string date_str(buffer);

    std::string stockNo = "0050";

    // compose api route
    std::string rootUrl = "www.twse.com.tw";
    std::stringstream ss;
    ss << "/rwd/zh/afterTrading/STOCK_DAY?date=" << date_str
       << "&stockNo=" << stockNo << "&response=json";
    std::string apiPath = ss.str();
    
    std::cout << "Request url: " << rootUrl << apiPath << "\n";

    // send http request
    httplib::SSLClient cli(rootUrl);
    auto res = cli.Get(apiPath.c_str());
    
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

    // print data
    // std::cout << "股票：" << data["title"] << "\n";
    // std::cout << "日期\t\t收盤價\n";

    // for (auto &row : data["data"]) {
    //     std::string date = row[0];
    //     std::string close = row[6];
    //     std::cout << date << "\t" << close << "\n";
    // }
    
    // save data into json file
    std::filesystem::path data_dir = "data";
    std::filesystem::create_directory(data_dir);

    std::filesystem::path filename  = data_dir / (stockNo + "_" + date_str + ".json");
    std::ofstream fout(filename);
    if (!fout) {
        std::cerr << "Failed to open file for writing\n";
        return 1;
    }

    fout << data["data"].dump(4);
    fout.close();

    std::cout << "Saved data to " << filename << "\n";

    return 0;
}