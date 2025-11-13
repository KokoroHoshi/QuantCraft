#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>

#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    try{
        std::string stock_symbol = "0050.TW";
        std::string range = "1y";
        std::string interval = "1d";

        // compose api route
        std::string rootUrl = "query1.finance.yahoo.com";
        std::string api = "/v8/finance/chart/" 
                          + stock_symbol 
                          + "?range=" + range 
                          + "&interval=" + interval;
        
        std::cout << "Request url: " << rootUrl << api << "\n";

        // send http request
        httplib::SSLClient cli(rootUrl);
        auto res = cli.Get(api.c_str());
        
        if (!res) throw std::runtime_error("Connection failed");

        if (res->status != 200) throw std::runtime_error("HTTP status: " + std::to_string(res->status));

        // save data into json file
        std::filesystem::path data_dir = "data";
        std::filesystem::create_directory(data_dir);
        
        std::filesystem::path filename  = data_dir / (stock_symbol + "_" + range + "_" + interval + ".json");
        std::ofstream fout(filename);
        if (!fout) throw std::runtime_error("Failed to open file for writing");
        
        fout << json::parse(res->body);
        fout.close();

        std::cout << "Saved data to " << filename << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}