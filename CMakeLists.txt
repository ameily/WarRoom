project(WarRoom)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

if(MINGW)
    set(DIST_SUBDIR win)
else(MINGW)
    set(DIST_SUBDIR linux)
endif(MINGW)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/dist/${DIST_SUBDIR})

add_subdirectory(libwar)
add_subdirectory(waredit)
