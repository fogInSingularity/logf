cmake_minimum_required(VERSION 3.21)

project(logf C)

add_library(${PROJECT_NAME})

include(defaults.cmake)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/logf.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logf-defaults
)

add_subdirectory(tests)