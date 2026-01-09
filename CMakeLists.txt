cmake_minimum_required(VERSION 3.20)
project(terraria_clone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# SFML (PINNED VERSION)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

# FastNoise2
FetchContent_Declare(
  FastNoise2
  GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
  GIT_TAG master
)
FetchContent_MakeAvailable(FastNoise2)

set(TGUI_BACKEND SFML_GRAPHICS CACHE STRING "" FORCE)
set(TGUI_BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG v1.4.0
)
FetchContent_MakeAvailable(TGUI)


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(terraria_clone ${SRC_FILES})

target_link_libraries(terraria_clone PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
  FastNoise2
  tgui
)

target_include_directories(terraria_clone PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${fastnoise2_SOURCE_DIR}/include
)
