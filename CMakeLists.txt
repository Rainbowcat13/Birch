cmake_minimum_required(VERSION 3.5)
project(Birch)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Birch
        AVL_tree.cpp
        mainwindow.cpp
        main.cpp
        )

target_link_libraries(Birch Qt5::Widgets)