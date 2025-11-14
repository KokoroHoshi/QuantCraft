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
protected:
    std::string name;
public:
    Strategy(const std::string& name) : name(name) {}

    virtual ~Strategy() = default;

    virtual std::vector<SignalPoint> generateSignals() = 0;

    std::string getName() const { return name; }
};

#endif