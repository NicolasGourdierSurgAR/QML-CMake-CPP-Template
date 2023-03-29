# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Automagically manage the resources
set(CMAKE_AUTORCC ON)

# HEADERS
set(SHOWCASE_HEADERS
    Modern/ModernStyle.hpp
)

# SOURCES
set(SHOWCASE_SOURCES
    Showcase.cpp
    Modern/ModernStyle.cpp
)

# LINKS
set(SHOWCASE_LINKS
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Ui
)

# RESOURCES
set(SHOWCASE_RESOURCES
    Showcase.qrc
)

# TEMPORARY variable to fill QML_IMPORT_PATH
set(INTERNAL_QML_IMPORT_PATH ${INTERNAL_QML_IMPORT_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE
    INTERNAL "INTERNAL_QML_IMPORT_PATH"
)

add_executable(SHOWCASE ${SHOWCASE_SOURCES} ${SHOWCASE_HEADERS} ${SHOWCASE_RESOURCES})
target_link_libraries(SHOWCASE PRIVATE ${SHOWCASE_LINKS})
target_include_directories(SHOWCASE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
