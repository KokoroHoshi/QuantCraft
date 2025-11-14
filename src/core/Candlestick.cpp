#include "Candlestick.h"

#include <iostream>

void Candlestick::print() const {
    std::cout << date 
              << " O:" << open 
              << " H:" << high
              << " L:" << low 
              << " C:" << close 
              << " V:" << volume 
              << "\n";
}