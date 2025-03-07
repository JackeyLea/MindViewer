cmake_minimum_required(VERSION 3.16)

project(MindViewer
    VERSION 1.0.0
    DESCRIPTION "Qt 6.8.1 (64bit) with MSVC 2022"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include QWT
include(qwt.cmake)

# Add source files
set(SOURCES
    src/curve.cpp
    src/dataparser.cpp
    src/indicator.cpp
    src/localfile.cpp
    src/main.cpp
    src/mainwidget.cpp
    src/retriver.cpp
    src/simulator.cpp
)

set(HEADERS
    include/curve.h
    include/dataparser.h
    include/icd.h
    include/indicator.h
    include/localfile.h
    include/mainwidget.h
    include/retriver.h
    include/simulator.h
)

set(UI_FILES
    ui/mainwidget.ui
    ui/retriver.ui
)

# Set up Qt resources
set(RESOURCE_FILES
    resource.qrc
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCE_FILES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
    qwt::qwt
)

# Enable automoc, autorcc, autouic
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

# Windows specific settings
if(WIN32)
    # Set application icon
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resource/icon/mind.ico")
    
    # Configure Windows RC file
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/windows_metadata.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/windows_metadata.rc
        @ONLY
    )
    
    target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/windows_metadata.rc
    )
endif()

# Installation rules
if(UNIX AND NOT APPLE)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
    )
endif() 