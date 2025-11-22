cmake_minimum_required(VERSION 3.15)
project(test C)

find_package(kpi REQUIRED)

add_executable(test test.c)
target_link_libraries(test kpi::kpi)
