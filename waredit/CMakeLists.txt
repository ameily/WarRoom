
include_directories(../libwar forms/widgets ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(waredit_srcs forms/WargearProfileEditDialog.cpp forms/widgets/RefPlainTextEdit.cpp forms/widgets/SearchLineEdit.cpp forms/ReferenceEditDialog.cpp forms/WarEditWindow.cpp forms/widgets/RefTextArea.cpp forms/WEW_Game.cpp forms/WEW_Race.cpp ListSearch.cpp main.cpp)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    # resource compilation for MinGW
    ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o
                        COMMAND windres.exe -I ${CMAKE_CURRENT_SOURCE_DIR}/forms/designer/icons -i ${CMAKE_CURRENT_SOURCE_DIR}/waredit.rc 
                             -o ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o )
    SET(waredit_srcs ${waredit_srcs} ${CMAKE_CURRENT_BINARY_DIR}/warediticon.o)
endif(MINGW)

qt4_automoc(${waredit_srcs})
qt4_add_resources(waredit_rcs forms/designer/images.qrc)

add_executable(waredit ${waredit_srcs} ${waredit_rcs})
target_link_libraries(waredit war ${QT_QTGUI_LIBRARY}) #${QT_QTCORE_LIBRARY}  ${QT_QTXML_LIBRARY})

install(TARGETS waredit RUNTIME DESTINATION bin)
