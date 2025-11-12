#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

class Stock {
private:
    static long long parseVolume(const std::string& str);
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

    static Stock fromJsonRow(const std::string& symbol, const std::vector<std::string>& row);
};

#endif // STOCK_H