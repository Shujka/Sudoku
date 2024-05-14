cmake_minimum_required(VERSION 3.27)
project(main_variant)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(main_variant main.cpp
        SudokuField/SudokuField.cpp
        SudokuField/SudokuField.h
        SudokuField/PlayersField.cpp
        SudokuField/PlayersField.h
        mainwindow/mainwindow.cpp
        mainwindow/mainwindow.h
        mainwindow/mainwindow.ui
)
target_link_libraries(main_variant
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

