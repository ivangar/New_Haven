cmake_minimum_required(VERSION 3.15)
project(COMP345_NewHavenProject VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB AbstractClassSources "Abstract Classes/*")
file(GLOB DataStructureSources "Data Structures/*")
file(GLOB DeckSources "Deck/*")
file(GLOB EnumSources "Enums/*")
file(GLOB GameBoardSources "GameBoard/*")
file(GLOB PlayerSources "Player/*")
file(GLOB ResourceSources "Resources/*")
file(GLOB VillageBoardSources "VillageBoard/*")
file(GLOB GameSources "Game/*")



add_executable(COMP345_NewHavenProject main.cpp ${AbstractClassSources} ${DataStructureSources} ${DeckSources} ${EnumSources} ${GameBoardSources} ${PlayerSources} ${ResourceSources} ${VillageBoardSources} ${GameSources} Enums/VillageBoardNames.h)