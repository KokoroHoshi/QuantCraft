#include "DoubleLineCrossover.h"

#include <algorithm>

std::vector<SignalPoint> DoubleLineCrossover::generateSignals () {
    std::vector<SignalPoint> signals;
    size_t n = std::min(fast.size(), slow.size());

    if (n < 2) return signals;

    signals.reserve(n / 10);

    size_t i = 1, j = 1;

    while (i < fast.size() && j < slow.size()) {
        if (fast[i].date < slow[j].date) {
            i++;
            continue;
        } else if (fast[i].date > slow[j].date)
        {
            j++;
            continue;
        }
        

        double prev_fast = fast[i - 1].value;
        double prev_slow = slow[j - 1].value;
        double curr_fast = fast[i].value;
        double curr_slow = slow[j].value;

        if (prev_fast <= prev_slow && curr_fast > curr_slow) {
            signals.push_back({fast[i].date, SignalType::BUY});
        } else if (prev_fast >= prev_slow && curr_fast < curr_slow) {
            signals.push_back({fast[i].date, SignalType::SELL});
        }

        i++;
        j++;
    }

    return signals;
}