//
// Created by Zachary Hynes on 2020-02-06.
//
#include <iostream>
#include <string>
#include "VGMapDriver.h"
#include "VGMap.h"


void VGMapDriver::villageGameBoardMapDriver() {
    VillageGameBoard* villageGameBoard = new VillageGameBoard("Village1");


    auto* building1 = new Building(ResourceTypes::WHEATFIELD, 6);
    auto* building2 = new Building(ResourceTypes::MEADOW, 6);
    auto* building3 = new Building(ResourceTypes::FOREST, 6);
    auto* building4 = new Building(ResourceTypes::QUARRY, 6);
    auto* building5 = new Building(ResourceTypes::WHEATFIELD, 6);
    auto* building6 = new Building(ResourceTypes::MEADOW, 5);
    auto* building7 = new Building(ResourceTypes::FOREST, 4);
    auto* building8 = new Building(ResourceTypes::QUARRY, 3);
    auto* building9 = new Building(ResourceTypes::WHEATFIELD, 2);
    auto* building10 = new Building(ResourceTypes::MEADOW, 1);

    villageGameBoard->placeBuildingXY(building1, 0, 0, false);
    villageGameBoard->placeBuildingXY(building2, 0, 1, true);
    villageGameBoard->placeBuildingXY(building3, 0, 2, true);
    villageGameBoard->placeBuildingXY(building4, 0, 3, true);
    villageGameBoard->placeBuildingXY(building5, 0, 4, true);

//    villageGameBoard->placeBuildingXY(building2, 3, 1, true);
//    villageGameBoard->placeBuildingXY(building3, 3, 2, true);
//    villageGameBoard->placeBuildingXY(building4, 3, 3, true);
//    villageGameBoard->placeBuildingXY(building5, 3, 4, true);

    villageGameBoard->placeBuildingXY(building6, 1, 0, true);
    villageGameBoard->placeBuildingXY(building7, 2, 0, true);
    villageGameBoard->placeBuildingXY(building8, 3, 0, true);
    villageGameBoard->placeBuildingXY(building9, 4, 0, true);
    villageGameBoard->placeBuildingXY(building10, 5, 0, true);

    villageGameBoard->placeBuildingXY(building6, 1, 2, true);
    villageGameBoard->placeBuildingXY(building7, 2, 2, true);
    villageGameBoard->placeBuildingXY(building8, 3, 2, true);
    villageGameBoard->placeBuildingXY(building9, 4, 2, true);
    villageGameBoard->placeBuildingXY(building10, 5, 2, true);

    // INVALID BUILDING PLACEMENTs
//    villageGameBoard->placeBuildingXY(building1, 0, 5 , false);
//    villageGameBoard->placeBuildingXY(building1, 6, 0 , false);

    villageGameBoard->printVillageGameBoardMap();

    villageGameBoard->printVillageGameBoardScore();
}






