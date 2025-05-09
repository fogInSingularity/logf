cmake_minimum_required(VERSION 3.21)

project(logf-tests C)

add_executable(${PROJECT_NAME})

# include(defaults.cmake)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logf-defaults
        logf
        m
        gmp
)