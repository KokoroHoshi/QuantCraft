#ifndef SIMPLESTRATEGY_H
#define SIMPLESTRATEGY_H

#include <vector>
#include <string>

#include "Indicators.h"
#include "Strategy.h"

class DoubleLineCrossover : public Strategy{
private:
    std::vector<IndicatorPoint> fast;
    std::vector<IndicatorPoint> slow;

public:
    DoubleLineCrossover(
        const std::vector<IndicatorPoint>& fast_line,
        const std::vector<IndicatorPoint>& slow_line
    ) : fast(fast_line), slow(slow_line) {}

    std::vector<SignalPoint> generateSignals() override;
};

#endif