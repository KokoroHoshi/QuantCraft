#include "Candlestick.h"

#include <iostream>

Candlestick::Candlestick(const std::string& date_,
                        double open_,
                        double high_,
                        double low_,
                        double close_,
                        long long volume_
                        ) : date(date_),
                            open(open_),
                            high(high_),
                            low(low_),
                            close(close_),
                            volume(volume_) {}

void Candlestick::print() const {
    std::cout << date 
              << " O:" << open 
              << " H:" << high
              << " L:" << low 
              << " C:" << close 
              << " V:" << volume 
              << "\n";
}