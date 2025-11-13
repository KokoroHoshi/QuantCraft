#include "Stock.h"
#include "JsonParser.h"

#include <iostream>
#include <vector>

#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

int main() {
    try {
        Stock stock("0050");

        std::vector<Candlestick> candles = Parser::parseTWSEJsonFile("data/0050_20251112.json");
        stock.addCandles(candles);

        std::vector<double> closes;
        std::vector<std::string> dates;
        const auto& cs = stock.getCandles();
        for (const auto& c : cs) {
            closes.push_back(c.close);
            dates.push_back(c.date);
        }

        plt::figure_size(1200, 600);
        
        std::vector<int> x(cs.size());
        std::iota(x.begin(), x.end(), 0);
        plt::plot(x, closes, "b.-");
        plt::xticks(x, dates);
        
        plt::title("0050 Daliy Close Price");
        plt::xlabel("Date");
        plt::ylabel("Close Price");
        plt::grid(true);

        plt::save("output/0050_close_plot.png");

        std::cout << "Saved output/0050_close_plot.png\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}