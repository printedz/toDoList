cmake_minimum_required(VERSION 3.5)
project(learnCmake VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(learnCmake main.c) 

target_link_libraries(learnCmake ${GTK4_LIBRARIES})




