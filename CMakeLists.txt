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
ui/open.png)

include(FetchContent)
find_package(gempyre REQUIRED)
include(gempyre)
include_directories(include)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
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
add_executable(${PROJECT_NAME} src/main.cpp src/mainwindow.cpp src/mainwindow.hpp src/music_player.cpp src/music_player.hpp src/tagreader.hpp src/tagreader.cpp ${resource_files} ${SOLOUD_SRCS} )
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/soloud/include)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} tag dl)

gempyre_add_resources(PROJECT ${PROJECT_NAME} TARGET include/resources.h SOURCES ${resource_files})
target_link_libraries (   ${PROJECT_NAME} 
   gempyre::gempyre
)
