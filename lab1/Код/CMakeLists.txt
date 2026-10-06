cmake_minimum_required(VERSION 4.2)
project(labs)

set(CMAKE_CXX_STANDARD 20)

add_executable(labs main.cpp
        scooter.cpp

)

target_sources(labs PRIVATE
        scooter.hpp
)
