cmake_minimum_required(VERSION 3.28.3)

project(QuantCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# === core library ===
add_library(core STATIC
    src/core/Candlestick.cpp 
    src/core/Stock.cpp
    src/core/Indicators.cpp
    src/core/Backtester.cpp
)
target_include_directories(core PUBLIC src/core)
target_link_libraries(core PUBLIC nlohmann_json::nlohmann_json)

# === io library ===
add_library(io STATIC
    src/io/JsonParser.cpp
)
target_include_directories(io PUBLIC src/io)
target_link_libraries(io PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

# === strategy library ===
file(GLOB SRC_STRATEGY "src/strategy/*.cpp")
add_library(strategy STATIC ${SRC_STRATEGY})
target_include_directories(strategy PUBLIC src/strategy)
target_link_libraries(strategy PUBLIC core)

# main
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE core io strategy nlohmann_json::nlohmann_json)

# fetch_stock
add_executable(fetch_stock src/io/fetch_stock.cpp)
target_link_libraries(fetch_stock PRIVATE httplib::httplib nlohmann_json::nlohmann_json)