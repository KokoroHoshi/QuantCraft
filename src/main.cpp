#include "Stock.h"
#include "JsonParser.h"

#include <vector>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Stock stock("0050");
        
        std::vector<Candlestick> candles = Parser::parseTWSEJsonFile("data/0050_20251112.json");

        stock.addCandles(candles);

        stock.print(5);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}