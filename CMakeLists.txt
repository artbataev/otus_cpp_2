cmake_minimum_required(VERSION 3.10)
project(otus_cpp_2 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)

add_executable(ip_filter ip_filter.cpp)