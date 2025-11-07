cmake_minimum_required(VERSION 3.27.8)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_executable(main
    src/main.cpp
    src/Animation.cpp
    src/Player.cpp
    src/Platform.cpp
    src/Collider.cpp
)

# Allow clean includes like #include "Player.h"
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

set(CMAKE_BUILD_TYPE Debug)

