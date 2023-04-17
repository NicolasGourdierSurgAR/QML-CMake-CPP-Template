# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Automagically manage the resources
set(CMAKE_AUTORCC ON)

# HEADERS
set(LIVERELOAD_HEADERS
    FileWatcher.hpp
    LiveReloadEngine.hpp
)

# SOURCES
set(LIVERELOAD_SOURCES
    FileWatcher.cpp
    LiveReloadEngine.cpp
    LiveReload.cpp
)

# LINKS
set(LIVERELOAD_LINKS
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
)

# RESOURCES
set(LIVERELOAD_RESOURCES
    LiveReload.qrc
)

# TEMPORARY variable to fill QML_IMPORT_PATH
set(INTERNAL_QML_IMPORT_PATH ${INTERNAL_QML_IMPORT_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE
    INTERNAL "INTERNAL_QML_IMPORT_PATH"
)

add_executable(LIVERELOAD ${LIVERELOAD_SOURCES} ${LIVERELOAD_HEADERS} ${SHOWCASE_RESOURCES})
target_link_libraries(LIVERELOAD PRIVATE ${LIVERELOAD_LINKS})
target_compile_definitions(LIVERELOAD PUBLIC
    SOURCES_DIRECTORY="${CMAKE_SOURCE_DIR}")
target_include_directories(LIVERELOAD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
