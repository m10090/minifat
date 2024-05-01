cmake_minimum_required(VERSION 3.17)
project(CMakeTutorial
    VERSION 1.0
    DESCRIPTION "minifat simulation"
    LANGUAGES C)

option(DEBUG_MODE "Enable debug mode" OFF)
add_executable(main
    ./main.c
    commands/files_commands.c
    commands/dir_commands.c
    commands/help.c
    items/files.c
    items/dir.c
    disk/virtual_disk.c
    disk/fat_table.c
    )
if(DEBUG_MODE)
    target_compile_definitions(main PRIVATE DEBUG)
endif()
