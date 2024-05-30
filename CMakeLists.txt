cmake_minimum_required(VERSION 3.17)
project(CMakeTutorial
    VERSION 1.0
    DESCRIPTION "minifat simulation"
    LANGUAGES C)


# if you are in the debug mode, you can use the following command to build the project
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
add_executable(main
    ./main.c
    commands/files_commands.c
    commands/dir_commands.c
    commands/help.c
    items/files.c
    items/dir.c
    disk/virtual_disk.c
    disk/fat_table.c)
  target_sources(main PUBLIC ./cli.h)
if(CMAKE_BUILD_TYPE STREQUAL "debug")
  message("Debug mode")
  target_compile_definitions(main PRIVATE DEBUG)
endif()
