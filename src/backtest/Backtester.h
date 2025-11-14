#ifndef BACKTESTER_H
#define BACKTESTER_H

#include <vector>
#include <string>

#include "Stock.h"
#include "Strategy.h"
#include "Trade.h"

class Backtester {
private:
    Stock stock;
    Strategy* strategy;
    bool allow_short;
    std::vector<Trade> trades;

    double getPriceByDate(const std::string& date) const;

    double computeTotalProfit() const;
    double computeWinRate() const;
public:
    Backtester(const Stock& stock, Strategy* strategy, bool allow_short = false)
        : stock(stock), strategy(strategy), allow_short(allow_short) {}

    void run(bool print_performance = true, const std::string& save_trades_path = "");

    void printPerformance() const;
    void saveTradesToJson(const std::string& path) const;
};

#endif