cmake_minimum_required(VERSION 3.21)
project(project1)
set(APPLICATION_LIBRARY GameLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# This sets the Mac icon for the program
#set(MACOSX_BUNDLE_ICON_FILE game.icns)
#set_source_files_properties(game.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(SOURCE_FILES main.cpp pch.h GameLib/MainFrame.cpp GameLib/MainFrame.h GameLib/GameView.cpp GameLib/GameView.h GameApp.cpp GameApp.h)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

add_subdirectory(Tests)