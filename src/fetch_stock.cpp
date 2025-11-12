#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <exception>

#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    try{
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
        
        if (!res) throw std::runtime_error("Connection failed");

        if (res->status != 200) throw std::runtime_error("HTTP status: " + std::to_string(res->status));

        json data = json::parse(res->body);
        if (data["stat"] != "OK") throw std::runtime_error("Invalid response from TWSE");
        
        // save data into json file
        std::filesystem::path data_dir = "data";
        std::filesystem::create_directory(data_dir);

        std::filesystem::path filename  = data_dir / (stockNo + "_" + date_str + ".json");
        std::ofstream fout(filename);
        if (!fout) throw std::runtime_error("Failed to open file for writing");

        fout << data["data"].dump(4);
        fout.close();

        std::cout << "Saved data to " << filename << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}