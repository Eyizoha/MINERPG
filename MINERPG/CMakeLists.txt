cmake_minimum_required(VERSION 3.10)
project(MINERPG)
include_directories(./)

file(GLOB_RECURSE src "刺客/*.cpp")
file(GLOB_RECURSE src2 "法师/*.cpp")
file(GLOB_RECURSE src3 "界面/*.cpp")
file(GLOB_RECURSE src4 "射手/*.cpp")
file(GLOB_RECURSE src5 "武士/*.cpp")
file(GLOB_RECURSE src6 "战士/*.cpp")
file(GLOB_RECURSE src7 "咒术/*.cpp")
file(GLOB_RECURSE src8 "装备/*.cpp")

add_executable(MINERPG ${src} ${src2} ${src3} ${src4} ${src5} ${src6} ${src7} ${src8} MINERPG.cpp)
target_link_libraries(MINERPG "winmm.lib")

add_definitions(-w)