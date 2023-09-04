cmake_minimum_required(VERSION 3.25)
project(ChessMatcher)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ChessMatcher main.cpp)
target_link_libraries(ChessMatcher ${OpenCV_LIBS})


