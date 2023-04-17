set(LIBRARY_NAME "ModernStyle")

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Automagically manage the resources
set(CMAKE_AUTORCC ON)

# Sources for the MODERN_STYLE library
set(MODERN_STYLE_SOURCES
    Modern/ModernStyle.hpp
)

# Headers for the MODERN_STYLE library
set(MODERN_STYLE_HEADERS
    Modern/ModernStyle.cpp
)

# Resources file for the MODERN_STYLE library
set(MODERN_STYLE_RESOURCES
    ModernStyle.qrc
)

# Links for the MODERN_STYLE library
set(MODERN_STYLE_LINKS
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
)

# Temporary variable to fill the QML_IMPORT_PATH
set(INTERNAL_QML_IMPORT_PATH    ${INTERNAL_QML_IMPORT_PATH}
                                "${CMAKE_CURRENT_SOURCE_DIR}"
                                CACHE INTERNAL "INTERNAL_QML_IMPORT_PATH"
)

 qt5_add_resources(MODERN_STYLE_RESOURCES_SOURCES ${MODERN_STYLE_RESOURCES})

# Generate the library
add_library(${LIBRARY_NAME} STATIC ${MODERN_STYLE_SOURCES} ${MODERN_STYLE_HEADERS} ${MODERN_STYLE_RESOURCES_SOURCES})
target_link_libraries(${LIBRARY_NAME} PRIVATE ${MODERN_STYLE_LINKS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
