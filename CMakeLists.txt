cmake_minimum_required(VERSION 3.28.3)

project(QuantCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

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

# draw_candlestick
add_executable(draw_candlestick src/viz/draw_candlestick.cpp)
target_link_libraries(draw_candlestick PRIVATE core io imgui::imgui implot::implot glfw OpenGL::GL nlohmann_json::nlohmann_json)