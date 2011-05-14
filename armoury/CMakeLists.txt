find_package(Qt4 COMPONENTS QtCore QtGui QtXml REQUIRED)
include(${QT_USE_FILE})
include_directories(../libwar ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(armoury_srcs forms/ArmouryWindow.cpp main.cpp)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    # resource compilation for MinGW
    ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/armouryicon.o
                        COMMAND windres.exe -I ${CMAKE_CURRENT_SOURCE_DIR} -i ${CMAKE_CURRENT_SOURCE_DIR}/armoury.rc 
                             -o ${CMAKE_CURRENT_BINARY_DIR}/armouryicon.o )
    SET(armoury_srcs ${armoury_srcs} ${CMAKE_CURRENT_BINARY_DIR}/armouryicon.o)
endif(MINGW)

qt4_automoc(${armoury_srcs})

add_executable(armoury ${armoury_srcs})
target_link_libraries(armoury war ${QT_LIBRARIES})

install(TARGETS armoury RUNTIME DESTINATION ${DIST_BINDIR})