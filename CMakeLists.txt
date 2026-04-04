cmake_minimum_required(VERSION 3.16)

#set(CMAKE_TOOLCHAIN_FILE "D:/CGame/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake"
#    CACHE STRING "Vcpkg toolchain file")

# Toolchain file is set in CMakePresets.json

project(SCALING_UMBRELLA VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add dependencies
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# No C++20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# LENGINE executable
add_executable(SCALING_UMBRELLA)

# LENGINE sources and headers
file(GLOB SCALING_UMBRELLA_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SCALING_UMBRELLA_SRC_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

set(SCALING_UMBRELLA_SOURCES ${SCALING_UMBRELLA_SOURCES} ${SCALING_UMBRELLA_SRC_SOURCES})

target_sources(SCALING_UMBRELLA PRIVATE ${SCALING_UMBRELLA_SOURCES})

# LENGINE include dirs
target_include_directories(SCALING_UMBRELLA PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Preprocessor defines
target_compile_definitions(SCALING_UMBRELLA PRIVATE
    MY_TEST_DEFINE
)

# Automatically links to these libs
target_link_libraries(SCALING_UMBRELLA PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)

# Add directories with any random loose .dlls or .libs here
target_link_directories(SCALING_UMBRELLA PRIVATE
  
)

# Set configuration properties for LENGINE
if(MSVC)
    target_compile_options(SCALING_UMBRELLA PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(SCALING_UMBRELLA PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# Set LENGINE as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SCALING_UMBRELLA)

# Filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${SCALING_UMBRELLA_SOURCES})

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
