cmake_minimum_required(VERSION 4.2.0)

project(libkpi
	VERSION 0.1.0
	LANGUAGE C)

add_library(kpi STATIC)

target_compile_options(kpi
	-Wall
	-Wextra
	-pedantic
)

target_include_directories(kpi PUBLIC include)
target_include_directories(kpi PRIVATE src)

add_subdirectory(src)
