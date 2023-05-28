cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)

project(ahang)

set(resource_files 
ui/index.html
ui/song.png
ui/style.css
ui/ir_sans.ttf
ui/song-light.png
ui/lightdark.png
ui/play.png
ui/stop.png
ui/open.png
ui/about.html
ui/about.png
ui/favicon.ico)

include(FetchContent)
find_package(gempyre REQUIRED)
include(gempyre)
include_directories(include)
if(UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif(UNIX)
find_library(TAGLIB taglib)

file(GLOB_RECURSE AUDIOSOURCE ${CMAKE_CURRENT_LIST_DIR}/soloud/src/audiosource/*.c*)
file(GLOB_RECURSE CORE ${CMAKE_CURRENT_LIST_DIR}/soloud/src/core/*.c*)
file(GLOB_RECURSE FILTER ${CMAKE_CURRENT_LIST_DIR}/soloud/src/filter/*.c*)
if(UNIX)
    file(GLOB_RECURSE BACKEND ${CMAKE_CURRENT_LIST_DIR}/soloud/src/backend/sdl/*.c*)
    add_compile_definitions(WITH_SDL2)
endif(UNIX)

if(WIN32)
    add_compile_definitions(WITH_MINIAUDIO) #You can hear clip sound in Linux
endif(WIN32)

set(SOLOUD_SRCS 
    soloud/src/backend/miniaudio/soloud_miniaudio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/soloud/src/c_api/soloud_c.cpp
    ${AUDIOSOURCE}
    ${CORE}
    ${FILTER}
    ${BACKEND}
)
add_executable(${PROJECT_NAME} src/main.cpp src/mainwindow.cpp src/mainwindow.hpp src/music_player.cpp src/music_player.hpp src/tagreader.hpp src/tagreader.cpp src/ahang_utils.hpp src/ahang_utils.cpp src/about_dialog.hpp src/about_dialog.cpp ${resource_files} ${SOLOUD_SRCS} )
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/soloud/include)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} tag dl)
endif(UNIX)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} tag)
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif(WIN32)

gempyre_add_resources(PROJECT ${PROJECT_NAME} TARGET include/resources.h SOURCES ${resource_files})
target_link_libraries (   ${PROJECT_NAME} 
   gempyre::gempyre
)
