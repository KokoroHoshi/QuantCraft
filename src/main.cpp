#include "Stock.h"
#include "JsonParser.h"
#include "Indicators.h"
#include "SimpleStrategy.h"

#include <vector>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Stock stock("0050");

        stock.addCandles(Parser::parseYfinanceJsonFile("data/0050.TW_1y_1d.json"));

        std::cout << "Loaded " << stock.candles.size() << " candlesticks.\n";
        stock.print(5);

        // indicators
        std::vector<std::string> dates;
        std::vector<double> closes;
        for (const auto& c : stock.candles) {
            dates.push_back(c.date);
            closes.push_back(c.close);
        }

        auto short_MA = Indicators::SMA(closes, dates, 5);
        auto long_MA = Indicators::SMA(closes, dates, 10);

        std::cout << "Calculated SMA(5) and SMA(10).\n";

        // signal
        auto signals = DoubleLineCrossover::generateSignals(short_MA, long_MA);

        std::cout << "Generated " << signals.size() << "signals.\n\n";
        for (const auto& s : signals) {
            std::cout << s.date << ":"
                      << (s.type == SignalType::BUY? "BUY" : "SELL")
                      << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}