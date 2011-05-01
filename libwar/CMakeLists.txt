
add_library(war SHARED WarPage.cpp WargearRefList.cpp RuleRefList.cpp ArmyUnitWargear.cpp ArmyUnit.cpp Army.cpp UnresolvedReference.cpp WargearRef.cpp RuleRef.cpp XmlObject.cpp WargearProfile.cpp RuleList.cpp Game.cpp Race.cpp Rule.cpp RuleSet.cpp WargearList.cpp UnitList.cpp Wargear.cpp UnitProfile.cpp Unit.cpp )
target_link_libraries(war ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})
install(TARGETS war LIBRARY DESTINATION lib)
