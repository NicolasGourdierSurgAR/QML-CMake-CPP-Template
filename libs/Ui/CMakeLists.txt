set(LIBRARY_NAME "Ui")

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Automagically manage the resources
set(CMAKE_AUTORCC ON)

# Sources for the ui library
set(UI_SOURCES
)

# Headers for the ui library
set(UI_HEADERS
)

# Resources file for the ui library
set(UI_RESOURCES
    Ui.qrc
)

# Links for the ui library
set(UI_LINKS
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
)

# Temporary variable to fill the QML_IMPORT_PATH
set(INTERNAL_QML_IMPORT_PATH    ${INTERNAL_QML_IMPORT_PATH}
                                "${CMAKE_CURRENT_SOURCE_DIR}"
                                CACHE INTERNAL "INTERNAL_QML_IMPORT_PATH"
)

 qt5_add_resources(UI_RESOURCES_SOURCES ${UI_RESOURCES})

# Generate the library
add_library(${LIBRARY_NAME} STATIC ${UI_SOURCES} ${UI_HEADERS} ${UI_RESOURCES_SOURCES})
target_link_libraries(${LIBRARY_NAME} PRIVATE ${UI_LINKS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
