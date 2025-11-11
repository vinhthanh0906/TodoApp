cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TodoApp VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# UI component source files
set(UI_SOURCES
    ui/ColorTheme.cpp
    ui/UIManager.cpp
)

# Utils component source files
set(UTILS_SOURCES
    utils/Task.cpp
    utils/TimeUtility.cpp
    utils/FileManager.cpp
    utils/AlertManager.cpp
    utils/TaskManager.cpp
    utils/TodoApp.cpp
    utils/Countdown.cpp
)

# Main application source
set(MAIN_SOURCE
    main.cpp
)

# Combine all sources
set(ALL_SOURCES
    ${UI_SOURCES}
    ${UTILS_SOURCES}
    ${MAIN_SOURCE}
)

# Create executable
add_executable(log ${ALL_SOURCES})

# Optional: Create static library for UI components
add_library(ui_lib STATIC ${UI_SOURCES})

# Optional: Create static library for Utils components
add_library(utils_lib STATIC ${UTILS_SOURCES})

# Link libraries to executable (if using separate libraries)
# target_link_libraries(todo_app ui_lib utils_lib)

# Installation rules
install(TARGETS log DESTINATION bin)

# Print configuration
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")