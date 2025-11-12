#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

#include "Candlestick.h"

struct CandleArrays {
    std::vector<double> x;
    std::vector<double> open;
    std::vector<double> high;
    std::vector<double> low;
    std::vector<double> close;
};

class Stock {
public:
    std::string symbol;
    std::vector<Candlestick> candles;

    Stock() = default;
    explicit Stock(const std::string& symbol);

    void print(int limit) const;
    
    void addCandle(const Candlestick& new_candle);
    void addCandles(const std::vector<Candlestick>& new_candles);

    const std::vector<Candlestick>& getCandles() const;

    CandleArrays getCandleArrays();
};

#endif // STOCK_H