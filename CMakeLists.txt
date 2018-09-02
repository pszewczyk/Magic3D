cmake_minimum_required(VERSION 2.8)

#project name
PROJECT(Magic3d)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(/usr/include/irrlicht)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -g -Wall")

ADD_EXECUTABLE(Magic3d
	src/action.cpp
	src/globalcrap.cpp
	src/logger.cpp
	src/mortal.cpp
	src/target.cpp
	src/camera.cpp
	src/icon.cpp
	src/machine.cpp
	src/npc.cpp
	src/window.cpp
	src/config.cpp
	src/interface.cpp
	src/main.cpp
	src/player.cpp
	src/world.cpp
	src/dcontainer.cpp
	src/inventory.cpp
	src/map.cpp
	src/primitives.cpp
	src/defstable.cpp
	src/io.cpp
	src/menu.cpp
	src/question.cpp
	src/drawable.cpp
	src/item.cpp
	src/mesh.cpp
	src/spellbar.cpp
	src/game.cpp
	src/keyboard.cpp
	src/minimap.cpp
	src/spellscreen.cpp)

TARGET_LINK_LIBRARIES(Magic3d Irrlicht ${pkgs_LDFLAGS})
