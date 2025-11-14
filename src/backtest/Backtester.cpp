#include "Backtester.h"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// private
double Backtester::getPriceByDate(const std::string& date) const {
    for (const auto& candle : stock.candles) {
        if (candle.date == date) {
            return candle.close;
        }
    }

    throw std::runtime_error("Price not found for date: " + date);
}

double Backtester::computeTotalProfit() const {
    double profit = 0.0;
    double position = 0.0;
    double entry_price = 0.0;

    for (const auto& trade : trades) {
        if (trade.type == TradeType::BUY) {
            if (position == 0) {
                position = 1.0;
                entry_price = trade.price;
            } else if (position == -1) {
                profit += entry_price - trade.price;
                position = 0;
            }
        } else if (trade.type == TradeType::SELL) {
            if (position == 1) {
                profit += trade.price - entry_price;
                position = 0;
            } else if (position == 0 && allow_short) {
                position = -1.0;
                entry_price = trade.price;
            }
        }
    }

    if (position != 0) {
        double last_price = trades.back().price;
        
        if (position == 1) {
            profit += last_price - entry_price;
        } else if (position == -1) {
            profit += entry_price - last_price;
        }
    }

    return profit;
}

double Backtester::computeWinRate() const {
    int wins = 0, trades_count = 0;

    for (size_t i = 1; i < trades.size(); i++) {
        const auto& prev = trades[i - 1];
        const auto& curr = trades[i];

        if (prev.type == TradeType::BUY && curr.type == TradeType::SELL) {
            trades_count++;
            if (curr.price > prev.price) wins++;
        } else if (prev.type == TradeType::SELL && curr.type == TradeType::BUY) {
            trades_count++;
            if (curr.price < prev.price) wins++;
        }
    }

    return trades_count == 0? 0.0 : static_cast<double> (wins) / trades_count;
}


void Backtester::run(bool print_performance, const std::string& save_trades_path) {
    trades.clear();
    
    auto signals = strategy->generateSignals();

    double position = 0.0;

    for (const auto& signal : signals) {
        double price = getPriceByDate(signal.date);

        if (signal.type == SignalType::BUY) {
            if (position == 0) {
                position = 1.0;
                trades.emplace_back(signal.date, TradeType::BUY, price, 1.0);
            } else if (position == -1) {
                trades.emplace_back(signal.date, TradeType::BUY, price, 1.0);
                position = 0;
            }
        } else if (signal.type == SignalType::SELL) {
            if (position == 1) {
                trades.emplace_back(signal.date, TradeType::SELL, price, 1.0);
                position = 0;
            } else if (position == 0 && allow_short) {
                position = -1;
                trades.emplace_back(signal.date, TradeType::SELL, price, 1.0);
            }
        }
    }

    if (print_performance) printPerformance();

    if (save_trades_path != "") saveTradesToJson(save_trades_path);
}

void Backtester::printPerformance() const {
    std::cout << "Total Profit: " << computeTotalProfit() << "\n";
    std::cout << "Win Rate: " << computeWinRate() << "%\n";
    std::cout << "Number of trades: " << trades.size() << "\n";
}

void Backtester::saveTradesToJson(const std::string& path) const {
    json trades_json = json::array();

    for (const auto& trade : trades) {
        trades_json.push_back({
            {"date", trade.date},
            {"type", trade.type == TradeType::BUY? "BUY" : "SELL"},
            {"price", trade.price},
            {"quantity", trade.quantity}
        });
    }

    std::filesystem::create_directory(std::filesystem::path(path).parent_path());

    std::ofstream out(path);

    if (!out.is_open()) {
        std::cerr << "[Error] Cannot open file: " << path << "\n";
        return;
    }

    out << trades_json.dump(4);
    out.close();

    std::cout << "[Info] Trades saved to " << path << "\n";
}