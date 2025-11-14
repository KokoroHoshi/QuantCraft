#include "Indicators.h"

#include <numeric>

std::vector<IndicatorPoint> Indicators::SMA(
    const std::vector<Candlestick>& candles,
    size_t period
) {
    std::vector<IndicatorPoint> result;

    if (candles.size() < period) return result;

    double sum = 0.0;
    for (size_t i = 0; i < period; i++) {
        sum += candles[i].close;
    }
    result.push_back({candles[period - 1].date, sum / period});

    for (size_t i = period; i < candles.size(); i++) {
        sum += candles[i].close - candles[i - period].close;
        result.push_back({candles[i].date, sum / period});
    }

    return result;
}