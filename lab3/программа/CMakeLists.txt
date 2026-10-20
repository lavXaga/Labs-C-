cmake_minimum_required(VERSION 4.2)
project(labs)

set(CMAKE_CXX_STANDARD 20)

add_executable(labs main.cpp
        history.cpp
        profile.cpp
        controller.cpp
        sensor.cpp


)

target_sources(labs PRIVATE
        history.hpp
        profile.hpp
        controller.hpp
        sensor.hpp
)