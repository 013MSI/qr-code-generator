cmake_minimum_required(VERSION 3.10)
project(qr-code-generator VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(qr-code-generator main.cpp ${SRC_FILES})
target_include_directories(qr-code-generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
