cmake_minimum_required(VERSION 3.25)
project(ColorPicking)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ColorPicking main.cpp HSVCalculator.cpp RGB2HSV.cpp trial.cpp)
target_link_libraries(ColorPicking ${OpenCV_LIBS})

