#ifndef SIMPLESTRATEGY_H
#define SIMPLESTRATEGY_H

#include <vector>
#include <string>

#include "Indicators.h"

enum class SignalType {
    HOLD,
    BUY,
    SELL 
};

struct SignalPoint {
    std::string date;
    SignalType type;
};

class DoubleLineCrossover {
public:
    static std::vector<SignalPoint> generateSignals (
        const std::vector<IndicatorPoint>& fast,
        const std::vector<IndicatorPoint>& slow
    );
};

#endif