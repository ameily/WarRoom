project(WarRoom)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

if(MINGW)
    set(DIST_LIBDIR win)
    set(DIST_BINDIR win)
else(MINGW)
    set(DIST_LIBDIR unix/lib)
    set(DIST_BINDIR unix/bin)
endif(MINGW)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/dist)

add_subdirectory(libwar)
add_subdirectory(waredit)
