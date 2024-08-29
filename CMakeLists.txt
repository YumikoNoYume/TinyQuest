cmake_minimum_required(VERSION 3.14)
project(TinyQuest)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML REQUIRED)

file(GLOB src_files src/Engine/*.cpp src/Game/*.cpp)
add_executable(TinyQuest ${src_files})
target_link_libraries(TinyQuest sfml::sfml)
include_directories(src/Engine)
