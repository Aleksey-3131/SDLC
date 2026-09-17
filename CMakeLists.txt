cmake_minimum_required(VERSION 3.16)
project(WeightConverterMVC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая обработка Qt-специфики (moc для Q_OBJECT и т.п.)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Сначала пробуем Qt6, если не найден — Qt5
find_package(Qt6 COMPONENTS Widgets QUIET)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS Widgets REQUIRED)
endif()

add_executable(WeightConverterMVC
    main.cpp
    WeightModel.h
    WeightModel.cpp
    WeightController.h
    WeightController.cpp
    InputDialog.h
    InputDialog.cpp
    MainWindow.h
    MainWindow.cpp
)

if (Qt6_FOUND)
    target_link_libraries(WeightConverterMVC PRIVATE Qt6::Widgets)
else()
    target_link_libraries(WeightConverterMVC PRIVATE Qt5::Widgets)
endif()
