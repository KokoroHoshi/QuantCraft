#include "Indicators.h"

#include <numeric>

std::vector<IndicatorPoint> Indicators::SMA(
    const std::vector<double>& data,
    const std::vector<std::string>& dates,
    size_t period
) {
    std::vector<IndicatorPoint> result;

    if (data.size() < period) return result;

    double sum = std::accumulate(data.begin(), data.begin() + period, 0.0);
    result.push_back({dates[period - 1], sum / period});

    for (size_t i = period; i < data.size(); i++) {
        sum += data[i] - data[i - period];
        result.push_back({dates[i], sum / period});
    }

    return result;
}