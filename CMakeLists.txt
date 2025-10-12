cmake_minimum_required(VERSION 3.20)
project(AtomOS LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)

# This is just for syntax highlighting, not building
add_executable(atomos_dummy
        kernel.c
        multiboot_header.S
)

# Prevent trying to link system libraries
set_target_properties(atomos_dummy PROPERTIES
        EXCLUDE_FROM_ALL TRUE
)