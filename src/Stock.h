#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
public:
    std::string symbol;
    std::string date; // YYYY-MM-DD
    double open;
    double high;
    double low;
    double close;
    long long volume;

    Stock() = default;
    Stock(const std::string& symbol,
            const std::string& date,
            double open,
            double high,
            double low,
            double close, 
            long long volume
    );

    void print() const;
};

#endif // STOCK_H