cmake_minimum_required(VERSION 3.10)

set(CMAKE_GENERATOR_PLATFORM win32)
project(PathFinder)
set(CMAKE_CXX_STANDARD 17)
include_directories(Vendor/imgui)
include_directories(Vendor/imgui-sfml)
include_directories(Vendor/SFML/include/)
link_directories(Vendor/SFML/build/lib/Debug)
link_directories(Vendor/SFML/build/lib/Release)
set(CMAKE_SUPPRESS_REGENERATION true)

file(GLOB PATH_FINDER_HPP "src/*.hpp")
file(GLOB PATH_FINDER_CPP "src/*.cpp")
set(SRC ${PATH_FINDER_HPP} ${PATH_FINDER_CPP} 
"Vendor/imgui/imgui.cpp" 
"Vendor/imgui/imgui_draw.cpp" 
"Vendor/imgui/imgui_tables.cpp"
"Vendor/imgui/imgui_widgets.cpp" 
"Vendor/imgui-sfml/imgui-SFML.h"
"Vendor/imgui-sfml/imgui-SFML.cpp")

add_executable(${PROJECT_NAME} ${SRC})