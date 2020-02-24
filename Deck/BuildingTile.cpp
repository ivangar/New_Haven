//
// Created by Zachary Hynes on 2020-02-07.
//

#include <iostream>
#include <iomanip>
#include "BuildingTile.h"

BuildingTile::BuildingTile(int cost) {
    this->buildingCost = new int(cost);
}

BuildingTile::~BuildingTile() {
    // TODO: Implement destructor.
}

void BuildingTile::printTile() {
    Building* thisTilesBuilding = this->getBuilding();
    int buildingCost = *this->getBuildingCost();

    if (thisTilesBuilding != nullptr) {
        thisTilesBuilding->printBuilding();
    } else {
        std::cout << "    " << std::setfill('0') << std::setw(2) << buildingCost << "   |";
    }
}

void BuildingTile::debugTile() {
    // TODO: Implement debugTile funreturn buildingCost;ction.
}
