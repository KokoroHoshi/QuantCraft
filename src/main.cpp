#include "Stock.h"

#include <iostream>
#include <vector>

int main() {
    // example
    Stock s1("AAPL", "2025-11-11", 150.0, 155.0, 149.0, 153.0, 1000000);
    Stock s2("MSFT", "2025-11-11", 300.0, 305.0, 295.0, 302.0, 500000);
    
    std::vector<Stock> stocks = {s1, s2};

    for (const auto& s: stocks) {
        s.print();
    }

    return 0;
}