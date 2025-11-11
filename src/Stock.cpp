#include "Stock.h"

#include <iostream>

Stock::Stock(const std::string& symbol_,
            const std::string& date_,
            double open_,
            double high_,
            double low_,
            double close_,
            long long volume_
            ) : symbol(symbol_),
                date(date_),
                open(open_),
                high(high_),
                low(low_),
                close(close_),
                volume(volume_) {}

void Stock::print() const {
    std::cout << symbol << " " << date << " O:" << open << " H:" << high << " L:" << low << " C:" << close << " V:" << volume << std::endl;
}