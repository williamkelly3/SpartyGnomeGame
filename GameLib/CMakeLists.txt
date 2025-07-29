project(GameLib)

set(SOURCE_FILES pch.h MainFrame.h MainFrame.cpp GameView.cpp GameView.h ids.h Game.cpp Game.h Item.cpp Item.h Level.cpp
        Level.h ItemBackground.cpp ItemBackground.h Scoreboard.cpp Scoreboard.h
        SpartyGnome.cpp SpartyGnome.h ItemDec.cpp ItemDec.h ItemMoney.cpp ItemMoney.h
        ItemWall.cpp ItemWall.h ItemTuitionUp.cpp ItemTuitionUp.h ItemDoor.cpp ItemDoor.h ItemVillain.cpp ItemVillain.h
        MoneyDec.cpp MoneyDec.h PlatformDec.cpp PlatformDec.h ItemPlatform.cpp ItemPlatform.h Vector.cpp Vector.h ItemInvincibility.cpp ItemInvincibility.h ItemVisitor.cpp ItemVisitor.h VerticalVisit.cpp VerticalVisit.h HorizontalVisit.cpp HorizontalVisit.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)