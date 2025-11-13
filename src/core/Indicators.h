#ifndef INDICATORS_H
#define INDICATORS_H

#include <vector>
#include <string>

struct IndicatorPoint {
    std::string date;
    double value;
};

namespace Indicators {
    std::vector<IndicatorPoint> SMA(
        const std::vector<double>& data,
        const std::vector<std::string>& dates,
        size_t period
    );
}

#endif