cmake_minimum_required(VERSION 3.9)
project(projektuppgift)

set(CMAKE_CXX_STANDARD 11)

add_executable(projektuppgift main.cpp constants.h menu.cpp menu.h userhandling.cpp userhandling.h search.cpp search.h file.cpp file.h sort.cpp sort.h utils.cpp utils.h print.cpp print.h)