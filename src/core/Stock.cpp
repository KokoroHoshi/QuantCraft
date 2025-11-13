#include "Stock.h"

#include <iostream>

Stock::Stock(const std::string& symbol_) : symbol(symbol_) {}

void Stock::print(int limit = -1) const {
    std::cout << "Stock: " << symbol << "\n";

    int printed = 0;
    for (const auto& candle : candles) {
        if (limit != -1 && printed >= limit) break;
        
        candle.print();
        
        printed++;
    }
}

void Stock::addCandle(const Candlestick& new_candle) {
    candles.push_back(new_candle);
}

void Stock::addCandles(const std::vector<Candlestick>& new_candles) {
    candles.reserve(candles.size() + new_candles.size());
    candles.insert(candles.end(), new_candles.begin(), new_candles.end());
}

const std::vector<Candlestick>& Stock::getCandles() const {
    return candles;
}
