cmake_minimum_required(VERSION 3.28.3)

project(QuantCraft)

set(CMAKE_CXX_STANDARD 17)

find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(main 
    src/main.cpp 
    src/Stock.cpp
)

add_executable(test_http src/test_http.cpp)
target_link_libraries(test_http PRIVATE httplib::httplib nlohmann_json::nlohmann_json)