#ifndef INDICATORS_H
#define INDICATORS_H

#include <vector>
#include <string>

#include "Candlestick.h"

struct IndicatorPoint {
    std::string date;
    double value;
};

namespace Indicators {
    std::vector<IndicatorPoint> SMA(
        const std::vector<Candlestick>& candles,
        size_t period
    );
}

#endif