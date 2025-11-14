#include "Stock.h"
#include "JsonParser.h"
#include "Indicators.h"
#include "DoubleLineCrossover.h"
#include "Backtester.h"

#include <vector>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // 1. Load stock data
        Stock stock(
            "0050", 
            Parser::parseYfinanceJsonFile("data/0050.TW_1y_1d.json")
        );

        std::cout << "Loaded " << stock.candles.size() << " candlesticks.\n";
        stock.print(5);

        // 2. Calculate indicators
        auto fast_MA = Indicators::SMA(stock.candles, 5);
        auto slow_MA = Indicators::SMA(stock.candles, 10);

        std::cout << "Calculated SMA(5) and SMA(10).\n";

        // 3. Setup strategy
        DoubleLineCrossover strategy(fast_MA, slow_MA);
        auto signals = strategy.generateSignals();

        std::cout << "Generated " << signals.size() << " signals.\n\n";
        for (const auto& s : signals) {
            std::cout << s.date << ":"
                      << (s.type == SignalType::BUY? "BUY" : "SELL")
                      << "\n";
        }

        // 4. Run backtest
        Backtester backtester(stock, &strategy, true);
        backtester.run(false);

        std::cout << "\nBacktest finished.\n";
        
        backtester.printPerformance();

        backtester.saveTradesToJson("output/trades.json");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}