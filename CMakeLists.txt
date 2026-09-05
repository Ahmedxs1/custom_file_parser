cmake_minimum_required(VERSION 3.16)

project(app LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(app
    ${SRC}
)

target_include_directories(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)