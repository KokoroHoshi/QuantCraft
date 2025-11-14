#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include <string>

enum class SignalType {
    HOLD,
    BUY,
    SELL 
};

struct SignalPoint {
    std::string date;
    SignalType type;
};

class Strategy {
public:
    virtual ~Strategy() = default;

    virtual std::vector<SignalPoint> generateSignals() = 0;
};

#endif