cmake_minimum_required(VERSION 3.20)
project(portfolio_site_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Drogon REQUIRED)

add_executable(site
    src/main.cpp
)

target_link_libraries(site PRIVATE Drogon::Drogon)