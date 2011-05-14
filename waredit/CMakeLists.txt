find_package(Qt4 COMPONENTS QtCore QtGui QtXml REQUIRED)
include(${QT_USE_FILE})
include_directories(../libwar ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(waredit_srcs forms/WarPageViewerDialog.cpp forms/WargearProfileEditDialog.cpp forms/ReferenceEditDialog.cpp forms/WarEditWindow.cpp forms/WEW_Game.cpp forms/WEW_Race.cpp ListSearch.cpp main.cpp)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    # resource compilation for MinGW
    ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o
                        COMMAND windres.exe -I ${CMAKE_CURRENT_SOURCE_DIR} -i ${CMAKE_CURRENT_SOURCE_DIR}/waredit.rc 
                             -o ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o )
    SET(waredit_srcs ${waredit_srcs} ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o)
endif(MINGW)

qt4_automoc(${waredit_srcs})


add_executable(waredit ${waredit_srcs})
target_link_libraries(waredit war ${QT_LIBRARIES}) #${QT_QTCORE_LIBRARY}  ${QT_QTXML_LIBRARY})

install(TARGETS waredit RUNTIME DESTINATION ${DIST_BINDIR})
