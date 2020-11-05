cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(~/CLionProjects/Assignment1/include)