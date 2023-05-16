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
    "${CMAKE_CURRENT_SOURCE_DIR}/src/a.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/array.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bind.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constexpr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constructor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/decltype.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/deque.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/final.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/for.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/forward.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/function.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lambda.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nullptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/operator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/override.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pair.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shared_ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/tuple.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/using.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/virtual.cpp"
)

foreach(mainfile IN LISTS mains)
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    target_link_libraries(${mainname} pthread m dl)

    install(TARGETS ${mainname} RUNTIME DESTINATION install)
endforeach()
