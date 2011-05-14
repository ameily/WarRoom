find_package(Qt4 COMPONENTS QtCore QtGui QtXml REQUIRED)
include(${QT_USE_FILE})
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}) #${CMAKE_CURRENT_SOURCE_DIR})

set(war_srcs widgets/RefPlainTextEdit.cpp widgets/RefTextArea.cpp widgets/WarPageViewer.cpp widgets/SearchLineEdit.cpp WarPage.cpp WargearRefList.cpp RuleRefList.cpp ArmyUnitWargear.cpp ArmyUnit.cpp Army.cpp UnresolvedReference.cpp WargearRef.cpp RuleRef.cpp XmlObject.cpp WargearProfile.cpp RuleList.cpp Game.cpp Race.cpp Rule.cpp RuleSet.cpp WargearList.cpp UnitList.cpp Wargear.cpp UnitProfile.cpp Unit.cpp)
qt4_automoc(${war_srcs})
qt4_add_resources(war_rcs resources/images.qrc)

add_library(war SHARED ${war_srcs} ${war_rcs})
target_link_libraries(war ${QT_LIBRARIES})
install(TARGETS war LIBRARY DESTINATION ${DIST_LIBDIR}
    ARCHIVE DESTINATION ${DIST_LIBDIR}
    RUNTIME DESTINATION ${DIST_LIBDIR}
)
