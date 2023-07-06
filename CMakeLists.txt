cmake_minimum_required(VERSION 3.0.0)
project(cpp)

#打开编译详细过程
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

add_definitions(-DSPDLOG)
add_definitions(-DNLOHMANN)

add_definitions("-Wall")

include_directories(
    ${PROJECT_SOURCE_DIR}/3rdparty
)

file(
    GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/a.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/array.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/atomic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bind.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/comparing.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constexpr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constructor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/copy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/count.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/decltype.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/deque.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/final.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/find.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/for.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/forward.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/friend.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/function.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/future.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/json.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lambda.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nullptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/operator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/override.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pair.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/reference.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/regex.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/set.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shared_ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sort.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/throw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/tuple.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/typename.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/unique_ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/using.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/virtual.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/volatile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/weak_ptr.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/designpattern/singleton.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/sort/quick.cpp"
)

foreach(mainfile IN LISTS mains)
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    target_link_libraries(${mainname} pthread m dl)

    install(TARGETS ${mainname} RUNTIME DESTINATION install)
endforeach()
