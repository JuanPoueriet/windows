cmake_minimum_required(VERSION 3.16)

project(ChromeTabsQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

add_executable(ChromeTabsQt
    resources.qrc
    src/main.cpp
    src/TabSession.h
    src/TabSession.cpp
    src/TabView.h
    src/TabView.cpp
    src/DashboardWidget.h
    src/DashboardWidget.cpp
    src/DataTableWidget.h
    src/DataTableWidget.cpp
    src/DetachableTabBar.h
    src/DetachableTabBar.cpp
    src/TabHost.h
    src/TabHost.cpp
    src/AppWindow.h
    src/AppWindow.cpp
    src/Sidebar.h
    src/Sidebar.cpp
    src/TopHeader.h
    src/TopHeader.cpp
    src/StatusBar.h
    src/StatusBar.cpp
    src/WindowManager.h
    src/WindowManager.cpp
)

target_link_libraries(ChromeTabsQt PRIVATE Qt6::Widgets Qt6::Svg)
