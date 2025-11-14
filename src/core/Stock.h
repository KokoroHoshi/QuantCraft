#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

#include "Candlestick.h"

class Stock {
public:
    std::string symbol;
    std::vector<Candlestick> candles;

    Stock() = default;
    explicit Stock(const std::string& symbol) : symbol(symbol) {};
    Stock(const std::string& symbol, const std::vector<Candlestick>& candles)
        : symbol(symbol), candles(candles) {}

    void print(int limit) const;
    
    void addCandle(const Candlestick& new_candle);
    void addCandles(const std::vector<Candlestick>& new_candles);

    const std::vector<Candlestick>& getCandles() const;
};

#endif // STOCK_H