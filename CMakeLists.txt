cmake_minimum_required(VERSION 3.21)

set(project_name QML-CMake-CPP-Template)
project(${project_name} VERSION 0.1 LANGUAGES CXX)

set(BUILD_SHARED_LIBS YES)

# CXX standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External dependendencies
find_package(Qt5 REQUIRED COMPONENTS Qml Quick QuickControls2)
if(Qt5_FOUND)
    message(STATUS "Qt found, version ${Qt5_VERSION}")
    message(STATUS "Qt dir ${Qt5_DIR} found.")
endif()

add_subdirectory(libs)
add_subdirectory(apps)

set(QML_IMPORT_PATH ${INTERNAL_QML_IMPORT_PATH} CACHE STRING "The path to find different qml modules" FORCE)
