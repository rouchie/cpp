cmake_minimum_required(VERSION 3.0.0)
project(cpp)

#打开编译详细过程
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

add_definitions(-DSPDLOG)

add_definitions("-Wall")

include_directories(
    ${PROJECT_SOURCE_DIR}/3rdparty
)

file(
    GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/a.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/b.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/constexpr.cpp"
)

foreach(mainfile IN LISTS mains)
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})

    install(TARGETS ${mainname} RUNTIME DESTINATION install)
endforeach()
