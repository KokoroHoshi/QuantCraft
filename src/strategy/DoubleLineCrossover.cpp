#include "DoubleLineCrossover.h"

#include <algorithm>

std::vector<SignalPoint> DoubleLineCrossover::generateSignals () {
    std::vector<SignalPoint> signals;
    size_t n = std::min(fast.size(), slow.size());

    if (n < 2) return signals;

    signals.reserve(n / 10);

    for (size_t i = 1; i < n; i++) {
        double prev_fast = fast[i - 1].value;
        double prev_slow = slow[i - 1].value;
        double curr_fast = fast[i].value;
        double curr_slow = slow[i].value;

        if (prev_fast <= prev_slow && curr_fast > curr_slow) {
            signals.push_back({fast[i].date, SignalType::BUY});
        } else if (prev_fast >= prev_slow && curr_fast < curr_slow) {
            signals.push_back({fast[i].date, SignalType::SELL});
        }
    }

    return signals;
}