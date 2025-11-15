#ifndef TRADE_H
#define TRADE_H

#include <string>

enum class TradeType {
    BUY,
    SELL
};

struct Trade {
    std::string date;
    TradeType type;
    double price;
    double quantity;

    Trade(const std::string& date, TradeType type, double price, double quantity)
        : date(date), type(type), price(price), quantity(quantity) {}
};

#endif