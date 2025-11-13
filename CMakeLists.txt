cmake_minimum_required(VERSION 3.28.3)

project(QuantCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

# src/core
add_library(core STATIC
    src/core/Candlestick.cpp 
    src/core/Stock.cpp
)
target_include_directories(core PUBLIC src/core)

# src/io
add_library(io STATIC
    src/io/JsonParser.cpp
)
target_include_directories(io PUBLIC src/io)
target_link_libraries(io PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

# main
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE core io nlohmann_json::nlohmann_json)

# fetch_stock
add_executable(fetch_stock src/io/fetch_stock.cpp)
target_link_libraries(fetch_stock PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

# test_plot
add_executable(test_plot src/viz/test_plot.cpp)
target_include_directories(test_plot PRIVATE 
    ${Python3_INCLUDE_DIRS} 
    ${Python3_NumPy_INCLUDE_DIRS}
    /usr/local/vcpkg/installed/x64-linux/include # for matplotlibcpp.h
)
target_link_libraries(test_plot PRIVATE
    core
    io
    nlohmann_json::nlohmann_json
    Python3::Python
    Python3::NumPy    
)