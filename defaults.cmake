set(TARGET logf-defaults)

add_library(${TARGET} INTERFACE)

target_compile_features(${TARGET}
    INTERFACE
        c_std_11
)

target_compile_options(${TARGET}
    INTERFACE
        -fdiagnostics-color=always
 
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wunused
        -Wformat=2

        # -fstack-protector-strong # inserts checks for buffer overflow
        # -fPIE -pie
        
        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
            -fsanitize=address,leak,undefined
            -fno-omit-frame-pointer

            -march=native
        >

        $<$<CONFIG:Release>:
            -O2
            -march=native
            -flto
            -DNDEBUG
        >
)

target_link_options(${TARGET}
    INTERFACE
        -fdiagnostics-color=always

        -Wall
        -Wextra
        # -fPIE -pie
        # -fuse-ld=mold
        -rdynamic

        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
            -fsanitize=address,leak,undefined
            -fno-omit-frame-pointer
            
            -march=native
        >

        $<$<CONFIG:Release>:
            -g
            -O2
            -march=native
            -flto
        >
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json