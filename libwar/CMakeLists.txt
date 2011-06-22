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
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}) #${CMAKE_CURRENT_SOURCE_DIR})

set(war_srcs helpers/WarLoaderHelper.cpp widgets/WarButtonBox.cpp widgets/RefPlainTextEdit.cpp widgets/RefTextArea.cpp widgets/WarPageViewer.cpp widgets/SearchLineEdit.cpp WarPage.cpp WargearRefList.cpp RuleRefList.cpp ArmyUnitWargear.cpp ArmyUnit.cpp Army.cpp UnresolvedReference.cpp WargearRef.cpp RuleRef.cpp XmlObject.cpp WargearProfile.cpp RuleList.cpp Game.cpp Race.cpp Rule.cpp RuleSet.cpp WargearList.cpp UnitList.cpp Wargear.cpp UnitProfile.cpp Unit.cpp HtmlNode.cpp)
qt4_automoc(${war_srcs})
qt4_add_resources(war_rcs resources/images.qrc)

add_library(war SHARED ${war_srcs} ${war_rcs})
target_link_libraries(war ${QT_LIBRARIES})
install(TARGETS war LIBRARY DESTINATION ${DIST_LIBDIR}
    ARCHIVE DESTINATION ${DIST_LIBDIR}
    RUNTIME DESTINATION ${DIST_LIBDIR}
)