cmake_minimum_required(VERSION 3.10)
project(qr-code-generator VERSION 1.0)

set (CMAKE_CXX_STANDARD 11)

find_package(fmt REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(qr-code-generator main.cpp ${SRC_FILES})
target_include_directories(qr-code-generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(qr-code-generator PRIVATE fmt::fmt)
