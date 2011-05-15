#
#   This file is part of the War Room project
#   Url: https://github.com/ameily/WarRoom
#   Copyright (C) 2011  Adam Meily <meily.adam@gmail.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

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
