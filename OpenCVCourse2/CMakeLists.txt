cmake_minimum_required(VERSION 3.15)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(opencvTest Chapter2.cpp Chapter3.cpp Chapter5.cpp Chapter6.cpp Chapter7.cpp Project1.cpp ColorPicker.cpp Project3.cpp main.cpp)
target_link_libraries(opencvTest ${OpenCV_LIBS})
