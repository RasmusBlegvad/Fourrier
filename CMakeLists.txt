cmake_minimum_required(VERSION 3.28)
project(FourierVisualizer CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wno-enum-compare -Wall")

# Add the executable with source files
add_executable(FV src/main.cpp
        src/Wav.cpp
        src/Sigproccesing.cpp
        src/App.cpp
        src/FileManager.cpp
        src/UI.cpp
)

# Set the paths for Raylib and Raygui include and lib directories
set(RAYLIB_INCLUDE "${CMAKE_SOURCE_DIR}/libs/raylib/include")
set(RAYLIB_LIB "${CMAKE_SOURCE_DIR}/libs/raylib/lib")
set(RAYGUI_INCLUDE "${CMAKE_SOURCE_DIR}/libs/raygui/include")


# Include the Raylib include directory
target_include_directories(FV PUBLIC ${RAYLIB_INCLUDE} ${RAYGUI_INCLUDE})

target_link_libraries(FV "${RAYLIB_LIB}/libraylib.a")

if (WIN32)
    target_link_libraries(FV winmm)
endif ()
