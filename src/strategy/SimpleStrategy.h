#ifndef SIMPLESTRATEGY_H
#define SIMPLESTRATEGY_H

#include <vector>
#include <string>

#include "Indicators.h"

enum class SignalType {
    NONE,
    LONG, // Buy
    SHORT // Sell
};

struct SignalPoint {
    std::string date;
    SignalType type;
};

class SimpleMAStrategy {
public:
    static std::vector<SignalPoint> generateSignals (
        const std::vector<IndicatorPoint>& short_MA,
        const std::vector<IndicatorPoint>& long_MA
    );
};

#endif