cmake_minimum_required(VERSION 3.13)
project(cartoonize)

set(CMAKE_CXX_STANDARD 17)
SET(OpenCV_DIR /drive/projects/cpp/installation/OpenCV-master/lib/cmake/opencv4)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cartoonize main.cpp)

target_link_libraries(cartoonize ${OpenCV_LIBRARIES})