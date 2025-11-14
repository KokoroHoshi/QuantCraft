#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>

class Candlestick {
public:
    std::string date; // YYYY-MM-DD
    double open;
    double high;
    double low;
    double close;
    long long volume;

    Candlestick() = default;
    Candlestick(const std::string& date, double open, double high, double low, double close, long long volume)
        : date(date), open(open), high(high), low(low), close(close), volume(volume) {}
    
    void print() const;
};

#endif // CANDLESTICK_H