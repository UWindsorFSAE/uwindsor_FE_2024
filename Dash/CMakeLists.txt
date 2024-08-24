cmake_minimum_required(VERSION 3.10)

project(MyQtApp VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(MyQtApp main.cpp)
target_link_libraries(MyQtApp Qt5::Widgets)
