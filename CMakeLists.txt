cmake_minimum_required(VERSION 3.15)
project(COMP345_NewHavenProject VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "GameBoard/*.cpp")

add_executable(COMP345_NewHavenProject ${SOURCES} main.cpp VillageBoard/VGMap.cpp VillageBoard/VGMap.h VillageBoard/VGMapDriver.cpp VillageBoard/VGMapDriver.h Deck/BuildingTile.cpp Deck/BuildingTile.h "Data Structures/Graph.cpp" "Data Structures/Graph.h" "Data Structures/Node.cpp" "Data Structures/Node.h" "Abstract Classes/AbstractGameTile.h" Enums/ResourceTypes.h "Data Structures/GraphDriver.cpp" "Data Structures/GraphDriver.h" Deck/Building.cpp Deck/Building.h Deck/HarvestTile.cpp Deck/HarvestTile.h)