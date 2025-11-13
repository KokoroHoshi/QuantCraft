#include "SimpleStrategy.h"

#include <algorithm>

std::vector<SignalPoint> SimpleMAStrategy::generateSignals (
    const std::vector<IndicatorPoint>& short_MA,
    const std::vector<IndicatorPoint>& long_MA
) {
    std::vector<SignalPoint> signals;
    size_t n = std::min(short_MA.size(), long_MA.size());

    if (n < 2) return signals;

    signals.reserve(n / 10);

    for (size_t i = 1; i < n; i++) {
        double prev_short = short_MA[i - 1].value;
        double prev_long = long_MA[i - 1].value;
        double curr_short = short_MA[i].value;
        double curr_long = long_MA[i].value;

        if (prev_short <= prev_long && curr_short > curr_long) {
            signals.push_back({short_MA[i].date, SignalType::LONG});
        } else if (prev_short >= prev_long && curr_short < curr_long) {
            signals.push_back({short_MA[i].date, SignalType::SHORT});
        }
    }

    return signals;
}