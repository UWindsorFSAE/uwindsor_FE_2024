cmake_minimum_required(VERSION 3.10)

project(main VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
)

# Add the Qt resource file for processing
qt5_add_resources(RESOURCE_RCC
    resources.qrc
)


add_executable(main ${SOURCES} ${RESOURCE_RCC})

target_link_libraries(main Qt5::Widgets)