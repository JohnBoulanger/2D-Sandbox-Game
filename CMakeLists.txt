cmake_minimum_required(VERSION 3.27)
project(terraria_clone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)

# SFML dependency
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# FastNoiseLite dependency (header-only)
FetchContent_Declare(
    FastNoiseLite
    GIT_REPOSITORY https://github.com/Auburn/FastNoiseLite.git
    GIT_TAG master
)
FetchContent_MakeAvailable(FastNoiseLite)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(terraria_clone ${SRC_FILES})

target_include_directories(terraria_clone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${fastnoiselite_SOURCE_DIR}
)

target_link_libraries(terraria_clone PRIVATE
    sfml-graphics
)
