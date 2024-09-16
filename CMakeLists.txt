cmake_minimum_required(VERSION 3.28)
project(FourierVisualizer CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-enum-compare")

# Add the executable with source files
add_executable(FV src/main.cpp
                 src/WavReader.cpp
                 src/WavReader.h)

# Set the paths for Raylib include and lib directories
set(RAYLIB_INCLUDE "${CMAKE_SOURCE_DIR}/libs/raylib/include")
set(RAYLIB_LIB "${CMAKE_SOURCE_DIR}/libs/raylib/lib")
set(RAYGUI_INCLUDE "${CMAKE_SOURCE_DIR}/libs/raygui/include")


# Include the Raylib include directory
target_include_directories(FV PUBLIC ${RAYLIB_INCLUDE} ${RAYGUI_INCLUDE})

# Link with the Raylib dynamic library (libraylibdll.a)
target_link_libraries(FV "${RAYLIB_LIB}/libraylib.a")

# Add system libraries required by Raylib on Windows
if (WIN32)
    target_link_libraries(FV winmm)
endif()
